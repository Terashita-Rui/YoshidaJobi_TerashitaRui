//PlayerPos管理クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerPos : MonoBehaviour
{
    //Playerプレハブ取得用
    [SerializeField]
    private GameObject playerPrefab;
    //乱数生成用最小値
    [SerializeField]
    private float min;
    //乱数生成用最大値
    [SerializeField]
    private float max;
    //乱数生成範囲を拡大する固定値
    [SerializeField]
    private float Expansion;
    //プレハブ生成時のpos.y
    [SerializeField]
    private float InsPosY;

    //stageオブジェクト
    private GameObject stage;
    //GoalPosオブジェクト
    private GameObject goalPos;
    //EnemyPosオブジェクト
    private GameObject enemyPos;
    //Goalオブジェクト
    private GameObject goal;
    //goalスクリプト
    private Goal goalScript;
    //EnemyWallオブジェクト
    private GameObject enemyWall;
    //EnemyWallスクリプト
    private EnemyWall enemyWallScript;
    //GameManagerオブジェクト
    private GameObject gameManager;
    //GameManagerスクリプト
    private GameManager gameManagerScript;
    //PlayerManagerオブジェクト
    private GameObject playerManager;
    //PlayerManagaerスクリプト
    private PlayerManager playerManagerScript;
    //ステージの大きさ参照
    private Vector3 stageScale;
    //Gateスクリプト(接触したゲートのを参照するのでStartでは何もしない)
    private Gate gateScript;
    //EnemyMovesスクリプト(Enemyに当たった時に取得するのでstartでは何もしない)
    private EnemyMove enemyMoveScript;
    //ゴールに向かう速さ(スクリプト中で実際に動作させる用)
    private float moveSpeed;
    //プレハブ生成した時のプレハブの向き
    private Quaternion rotation;
    //プレハブインスタンス用変数
    private GameObject playerPrefabIns;
    //キー操作のX軸移動で使う
    private float KeyInputX;
    //audioSource
    private AudioSource audioSource;

    //Gate通ったかどうか
    public bool IsinGate;
    //子要素の数
    public int playerChildNum;
    //Instansコルーチン終了判定
    public bool InsColFin;
    //Destroyコルーチン終了判定
    public bool DesColFin;
    //PlayerNumが増えたら鳴らす
    public AudioClip addPlayerNumSE;
    //PlayerNumが減ったら鳴らす
    public AudioClip ReusePlayerNumSE;
    //ゴールしたら鳴らす
    public AudioClip InGoalSE;
    //EnemyMoveのIsHitPlayerが切り替わったかどうか
    public bool IsisHitPlayer;
    //ゲート通ってplayerChildNumが0になったか
    public bool IsDead;
    //goalPosについたかどうか
    public bool IsgoalPos;
    //EnemyPosに当たったかどうか
    public bool IsHitEnemyPos;

    void Start()
    {
        //各要素参照したり初期化したりする

        stage = GameObject.Find("stage");
        stageScale = stage.GetComponent<Transform>().localScale;
        goalPos = GameObject.Find("GoalPos");
        enemyPos = GameObject.Find("EnemyPos");

        goal = GameObject.Find("Goal");
        goalScript = goal.GetComponent<Goal>();
        gameManager = GameObject.Find("GameManager");
        gameManagerScript = gameManager.GetComponent<GameManager>();
        playerManager = GameObject.Find("PlayerManager");
        playerManagerScript = playerManager.GetComponent<PlayerManager>();
        enemyWall = GameObject.Find("EnemyWall");
        enemyWallScript = enemyWall.GetComponent<EnemyWall>();

        audioSource = GetComponent<AudioSource>();
        moveSpeed = 0.07f;
        IsisHitPlayer = false;
        IsDead = false;
        IsgoalPos = false;
        IsHitEnemyPos = false;

        //シード値
        Random.InitState(System.DateTime.Now.Millisecond);

        //子要素の数を参照
        playerChildNum = this.transform.childCount;

        IsinGate = false;
        InsColFin = false;
        DesColFin = false;

        //始まるときにプレイヤーを1つ生成しておく
        playerPrefabIns = Instantiate(playerPrefab, this.transform.position, rotation);
        //親指定
        playerPrefabIns.transform.parent = this.gameObject.transform;
    }

    void Update()
    {
        //子要素の数を参照
        playerChildNum = this.transform.childCount;
        //シード値
        Random.InitState(System.DateTime.Now.Millisecond);
        //キー入力した情報を入れる
        KeyInputX = Input.GetAxisRaw("Horizontal");
        //キー操作したときに動かすpos
        Vector3 Pos;

        //何かキーを押さないと移動させないようにする
        if (gameManagerScript.IsAnykey == true)
        {
            //移動処理
            //子要素が1つ以上なら
            if (playerChildNum >= 1)
            {//GoalPosに向かって動く
                transform.Translate(0, 0, moveSpeed);

                //移動範囲を制限しつつキー入力でPos.Xを動かす
                if (Input.GetKey(KeyCode.A) == true)
                {
                    if (transform.position.x > (stageScale.x) / 2 * -1)
                    {
                        Pos = new Vector3(KeyInputX * moveSpeed, 0.0f, 0.0f);
                        //自身のtransform.positionをキー入力で動くようにする
                        this.gameObject.transform.position += Pos;
                    }
                }
                if (Input.GetKey(KeyCode.D) == true)
                {
                    if (transform.position.x < (stageScale.x) / 2)
                    {
                        Pos = new Vector3(KeyInputX * moveSpeed, 0.0f, 0.0f);
                        //自身のtransform.positionをキー入力で動くようにする
                        this.gameObject.transform.position += Pos;
                    }
                }

                //EnemyWallに当たったらEnemyPosに向かうようにする
                if (enemyWallScript.IsWallHitPlayer == true)
                {
                    transform.position = Vector3.MoveTowards(transform.position, new Vector3(0.0f,InsPosY, enemyPos.transform.position.z), moveSpeed * 2);

                    if(DesColFin == true)
                    {
                        transform.Translate(0, 0, moveSpeed);
                    }
                }

                //goalPosで止まるようにする
                if (goalScript.IsGoal == true)
                {
                    transform.position = Vector3.MoveTowards(transform.position, new Vector3(0.0f, InsPosY, goalPos.transform.position.z), moveSpeed);
                    IsgoalPos = true;
                }
            }
            //Playerが全部消えたら
            else
            {//動かなくする
                moveSpeed = 0;
                IsDead = true;
                transform.position = Vector3.MoveTowards(transform.position, new Vector3(0.0f, 0.0f, 0.0f), moveSpeed);
            }
        }
    }

    private void OnTriggerEnter(Collider collider)
    {
        if(collider.gameObject.tag == "EnemyPos")
        {
            IsHitEnemyPos = true;
        }

        if(collider.gameObject.tag == "Goal")
        {
            audioSource.PlayOneShot(InGoalSE);
        }

        //どれかのゲートに入ったら
        if (collider.gameObject.tag == "PlusGate"
         || collider.gameObject.tag == "MinusGate"
         || collider.gameObject.tag == "MultiplicationGate")
        {
            IsinGate = true;

            //当たったゲートのスクリプトを参照する
            gateScript = collider.GetComponent<Gate>();

            if (IsinGate == true)
            {
                if (gateScript.gateType == Gate.GateType.plus
                 || gateScript.gateType == Gate.GateType.multiplication)
                {
                    audioSource.PlayOneShot(addPlayerNumSE);
                    StartCoroutine("PlayerPrefabInstantiate");
                }
                else if (gateScript.gateType == Gate.GateType.minus)
                {
                    audioSource.PlayOneShot(ReusePlayerNumSE);
                    StartCoroutine("PlayerPrefabDestroy");
                }
            }
        }

    }
    void OnTriggerExit(Collider collider)
    {
        if (collider.gameObject.tag == "PlusGate"
         || collider.gameObject.tag == "MinusGate"
         || collider.gameObject.tag == "MultiplicationGate")
        {
            gateScript = collider.GetComponent<Gate>();

            IsinGate = false;
        }
        if (collider.gameObject.tag == "EnemyPos")
        {
            IsHitEnemyPos = false;
        }
    }

    //プレハブをインスタンスするコルーチン
    IEnumerator PlayerPrefabInstantiate()
    {
        IsDead = false;
        if (IsinGate == true)
        {
            //ゲートが＋ゲートなら
            if (gateScript.GetGateType() == Gate.GateType.plus)
            {
                for (int nPCount = 0; nPCount < gateScript.addPlayerNum; nPCount++)
                {
                    //シード値
                    Random.InitState(System.DateTime.Now.Millisecond);
                    //addPlayerNumで増える分だけ生成する
                    playerPrefabIns = Instantiate(playerPrefab, new Vector3(Random.Range(this.transform.position.x + min,this.transform.position.x + max), InsPosY, Random.Range(this.transform.position.z + min, this.transform.position.z)), rotation);
                    //生成したプレハブの親指定
                    playerPrefabIns.transform.parent = this.gameObject.transform;
                    //持っている子要素の数を変えたのでPlayerManagerScriptのplayerPrefabNumを子要素の数に合わせる
                    playerManagerScript.playerPrefabNum = playerChildNum;

                    IsinGate = false;
                }

                yield return null;
            }

            //ゲートが＊ゲートなら
            if (gateScript.GetGateType() == Gate.GateType.multiplication)
            {
                IsDead = false;
                for (int nCount = 0; nCount < playerChildNum; nCount++)
                {//子要素を元々持っていた数*Xにするので一度今の子要素を全部消す
                    Destroy(transform.GetChild(nCount).gameObject);
                }

                //playerManagerScript.playerNumが元々持っていた子要素*gateScript.addPlayerNumなのでここで増やす
                for (int nCount = 0; nCount < (gameManagerScript.GPlayerNum * gateScript.addPlayerNum); nCount++)
                {
                    //シード値
                    Random.InitState(System.DateTime.Now.Millisecond);
                    //PlaeyrManagerのplayerPrefabNum分だけ生成する
                    playerPrefabIns = Instantiate(playerPrefab, new Vector3(Random.Range(this.transform.position.x + min, this.transform.position.x + max), InsPosY, Random.Range(this.transform.position.z + min, this.transform.position.z)), rotation);
                    //生成したプレハブの親指定
                    playerPrefabIns.transform.parent = this.gameObject.transform;
                    //持っている子要素の数を変えたのでPlayerManagerScriptのplayerPrefabNumを子要素の数に合わせる
                    playerManagerScript.playerPrefabNum = playerChildNum;

                    IsinGate = false;
                }
                yield return null;
            }

            //インスタンスコルーチン終了判定
            InsColFin = true;
        }
    }

    //プレハブを消すコルーチン
    IEnumerator PlayerPrefabDestroy()
    {
        if (IsinGate == true)
        {
            //ゲートがマイナスゲートなら
            if (gateScript.gateType == Gate.GateType.minus)
            {
                for (int nCount = 0; nCount < gateScript.addPlayerNum; nCount++)
                {
                    if (playerChildNum <= 0)
                    {
                        playerManagerScript.playerPrefabNum = playerChildNum;
                        DesColFin = true;
                        IsDead = true;
                        yield break;
                    }

                    Destroy(transform.GetChild(0).gameObject);
                    //持っている子要素の数を変えたのでPlayerManagerScriptのplayerPrefabNumを子要素の数に合わせる
                    playerManagerScript.playerPrefabNum = playerChildNum;

                    yield return null;
                }
            }
            IsinGate = false;
            //デストロイコルーチン終了
            DesColFin = true;
        }
    }
}