//プレイヤークラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Player : MonoBehaviour
{
    //移動速度
    [SerializeField]
    private float moveSpeed;
    //速度制限
    [SerializeField]
    private float limitSpeed;
    //Playerの直径が大きくなったら大きくするコライダーの半径
    [SerializeField]
    private float addColliderRadius = 0.01f;
    //子要素が増えたら強くする疑似重力の強さ
    [SerializeField]
    private float addGravity;
    //ダッシュエフェクト
    [SerializeField]
    private ParticleSystem dashEffect;

    //PlayerDiameterオブジェクト
    private GameObject playerDiameterObj;
    //PlayerDiameterスクリプト
    private PlayerDiameter playerDiameterScript;
    //GameManagerオブジェクト
    private GameObject gamaManagerObj;
    //GameManagerスクリプト
    private GameManager gameManagerScript;
    //リジットボディ参照
    private Rigidbody rigidBody;
    //Playerオブジェクトのスフィアコライダー
    private SphereCollider sphereCollider;
    //カメラの正面方向
    private Vector3 cameraForward;
    //移動方向ベクトル
    private Vector3 moveVector;
    //疑似重力
    private float gravity = -100.0f;
    //疑似重力を一旦保存しておく変数
    private float saveGravity;
    //DashCTが終わっているか
    private bool IsDashCT = false;
    //現在の直径
    private float currentDiameter;
    //現在のPlayrChildNum
    private int currentChildNum;
    //PlayerChildNumが増えた回数
    private int addChildNumCount;
    //ダッシュエフェクトを使用していいか
    private bool IsPlayDashEffect = false;
    //ダッシュエフェクトを表示する時間
    private float dashEffectPlayingTime = 0.0f;


    //Playerに当たったItemについているItemScript(当たったら取得するからStartでは何もしない
    [System.NonSerialized]
    public Item itemScript;
    //Playerに当たったItemについているMoveItemScript(当たったら取得するからStartでは何もしない
    [System.NonSerialized]
    public Item moveItemScript;
    //Playerが一定以上大きくなったか
    [System.NonSerialized]
    public bool IsAboutPlayerDiameter;
    //Dashを使えるか
    [System.NonSerialized]
    public bool IsPossibleDash = false;
    //Dashのクールタイム
    [System.NonSerialized]
    public float dashCT = 10.0f;
    //一番最後に子になったオブジェクト
    [System.NonSerialized]
    public GameObject lastChildObj;
    //Itemに当たったか
    [System.NonSerialized]
    public bool IsHitItem = false;
    //操作可能かどうか
    [System.NonSerialized]
    public bool IsOperable = true;

    //Playerオブジェクトの子の数
    public int playerChildNum;

    void Start()
    {
        //各要素を参照したり入れたりする

        playerDiameterObj = GameObject.Find("PlayerDiameter");
        playerDiameterScript = playerDiameterObj.GetComponent<PlayerDiameter>();
        gamaManagerObj = GameObject.Find("GameManager");
        gameManagerScript = gamaManagerObj.GetComponent<GameManager>();
        rigidBody = this.GetComponent<Rigidbody>();
        sphereCollider = this.transform.GetComponent<SphereCollider>();
        saveGravity = gravity;

        currentDiameter = playerDiameterScript.currentDimeter;

        //他のシーンに行っても破棄されなくする
        DontDestroyOnLoad(this.gameObject);
    }

    void Update()
    {
        //ゲームシーンなら
        if (SceneManager.GetActiveScene().name == "Game"
            || SceneManager.GetActiveScene().name == "game")
        {
            GameUpdate();
        }

        if (SceneManager.GetActiveScene().name == "Result"
            || SceneManager.GetActiveScene().name == "result")
        {
            ResultUpdate();
        }
    }

    //ダッシュ関数
    void Dash()
    {
        if (IsPossibleDash == true)
        {
            //Playerを走らせる
            rigidBody.AddForce(new Vector3(moveVector.x * 10.0f, 0, moveVector.z * 10.0f) * moveSpeed, ForceMode.Impulse);

            //CTリセット
            dashCT = 10.0f;

            //ダッシュエフェクトを表示できるようにする
            IsPlayDashEffect = true;

            //CTリセットするので使えなくする
            IsPossibleDash = false;
        }
    }

    //リジットボディで移動するのでFixeUpdate
    void FixedUpdate()
    {
        if (SceneManager.GetActiveScene().name == "Game"
            || SceneManager.GetActiveScene().name == "game")
        {
            GameFixedUpdate();
        }

        if (SceneManager.GetActiveScene().name == "Result"
            || SceneManager.GetActiveScene().name == "result")
        {
            ResultFixedUpdate();
        }
    }


    //ゲームシーンでのプレイヤーのUpdate処理
    void GameUpdate()
    {
        //子要素の数を入れる
        playerChildNum = this.gameObject.transform.childCount;

        //子が増えたら
        if (currentChildNum < playerChildNum)
        {
            //playerChildNumと数を合わせる
            currentChildNum = playerChildNum;
            //カウントを進める
            addChildNumCount = addChildNumCount + 1;
        }

        //最初のカウントダウンが終わるまで何も出来ないようにする
        if (gameManagerScript.IsEndCountDown == true)
        {

            if (IsDashCT == false)
            {
                //ダッシュが出来ないときだけ減らしていく
                dashCT -= Time.deltaTime;
            }
            //ダッシュエフェクトを表示していいなら
            if(IsPlayDashEffect == true)
            {
                dashEffectPlayingTime += Time.deltaTime;
            }
            //dashCTが0以下ならdashCTを減算しないようにする
            if (dashCT <= 0)
            {
                //ダッシュできるようにする
                IsDashCT = true;
            }
            else
            {
                //次のCTまでダッシュを出来なくする
                IsDashCT = false;
            }

            //Playerの子要素の要素を消していいか
            if (playerDiameterScript.IsDestroy == true)
            {
                //消えないと困るから念のため子要素の数だけ回す
                for (int nCount = 0; nCount < playerChildNum; nCount++)
                {
                    if (lastChildObj != null)
                    {
                        //各要素を消す
                        Destroy(this.transform.GetChild(nCount).GetComponent<Rigidbody>());
                        Destroy(this.transform.GetChild(nCount).GetComponent<Collider>());
                    }
                }

                playerDiameterScript.IsDestroy = false;
            }

            //プレイヤーの子が10回増えたら
            if (addChildNumCount >= 10)
            {
                IsAboutPlayerDiameter = true;

                //大きくなった直径と現在の直径を合わせる
                currentDiameter = playerDiameterScript.currentDimeter;
            }

            if (IsAboutPlayerDiameter == true)
            {
                //コライダーを大きくする
                sphereCollider.radius = sphereCollider.radius + addColliderRadius;
                //速度を遅くする
                moveSpeed = moveSpeed - 10;

                if (gravity < saveGravity)
                {
                    //saveGravityをgravityと合わせておく
                    saveGravity = gravity;
                }

                //リセットする
                addChildNumCount = 0;
            }

            //一定秒数経過したら
            if (dashCT <= 0)
            {
                //走れるようにする
                IsPossibleDash = true;
            }
        }
    }

    //ゲームシーンでのプレイヤーのFixedUpdate処理
    void GameFixedUpdate()
    {
        //カウントダウンが終わってるなら
        if (gameManagerScript.IsEndCountDown == true)
        {
            if (IsOperable == true)
            {
                //移動キーの入力を取得
                //縦
                float horizonal = Input.GetAxis("Horizontal");
                //横
                float vertical = Input.GetAxis("Vertical");

                //カメラの方向からXZ平面の単位ベクトル取得
                cameraForward = Vector3.Scale(Camera.main.transform.forward, new Vector3(1, 0, 1)).normalized;
                //移動方向ベクトルを設定
                moveVector = cameraForward * vertical + Camera.main.transform.right * horizonal;

                //移動
                rigidBody.AddForce(new Vector3(moveVector.x, 0, moveVector.z) * moveSpeed, ForceMode.Force);
                //下に力を加えることで疑似的にPlayerだけ重力を強くした状態にする
                rigidBody.AddForce(new Vector3(0.0f, gravity, 0.0f), ForceMode.Acceleration);

                //左シフト押したら
                if (Input.GetKey(KeyCode.LeftShift))
                {
                    //ダッシュ
                    Dash();
                }
                //スペース押したら
                if (Input.GetKey(KeyCode.Space))
                {
                    //動きを止める
                    rigidBody.velocity = Vector3.zero;
                    //ダッシュエフェクトを消す
                    dashEffect.Stop();
                }

                //速度制限に引っかかったら
                if (rigidBody.velocity.magnitude > limitSpeed)
                {
                    //制限速度まで速度を落とす
                    rigidBody.velocity = rigidBody.velocity.normalized * limitSpeed;
                }

                //ダッシュエフェクト表示してもいいなら
                if(IsPlayDashEffect == true)
                {
                    //ダッシュエフェクトを表示
                    dashEffect.Play();

                    if(dashEffectPlayingTime >= 1.0f)
                    {
                        //ダッシュエフェクトを消す
                        dashEffect.Stop();
                        //各要素リセット
                        dashEffectPlayingTime = 0.0f;
                        IsPlayDashEffect = false;

                    }
                }

            }
            else if (IsOperable == false)
            {
                //動きを止める
                rigidBody.velocity = Vector3.zero;
            }
        }
    }

    //リザルトシーンでのプレイヤーのUpdate処理
    void ResultUpdate()
    {
        //リザルトから遷移する時に保持しておく必要はないので、DontDestroyOnLoadを解除する
        SceneManager.MoveGameObjectToScene(this.gameObject, SceneManager.GetActiveScene());
    }

    //リザルトシーンでのプレイヤーのFixedUpdate処理
    void ResultFixedUpdate()
    {
        //何もしないと落ちていくからリギッドボディを消しておく
        Destroy(rigidBody);

        //位置と回転を0にする
        this.transform.position = new Vector3(0.0f, 0.0f, 0.0f);
        this.transform.rotation = Quaternion.Euler(0.0f, 0.0f, 0.0f);
    }

    void OnCollisionEnter(Collision collision)
    {
        if (collision.transform.tag == "Item")
        {
            //当たったItemのItemScriptを取得する
            itemScript = collision.transform.GetComponent<Item>();

            //ItemScriptを取得出来てるか確認
            if (itemScript != null)
            {
                //子要素に出来るなら
                if (itemScript.IsStick == true)
                {
                    collision.transform.GetComponent<Collider>().isTrigger = true;

                    //Itemを子要素にする
                    collision.transform.parent = this.gameObject.transform;

                    //当たって子になったオブジェクトを取得
                    lastChildObj = this.transform.GetChild(playerChildNum).gameObject;

                    //Itemに当たったのでtrue
                    IsHitItem = true;
                }
            }
        }
    }

    void OnCollisionStay(Collision collision)
    {
        if(collision.transform.name == "Slope")
        {
            //坂を登れるようにするために疑似重力を弱くする
            gravity = -10;
        }
        else
        {
            gravity = saveGravity;
        }
    }

    void OnCollisionExit(Collision collision)
    {
        if(collision.transform.name == "Slope")
        {
            //坂を抜けたら疑似重力を元に戻す
            gravity = saveGravity;
        }
    }
}
