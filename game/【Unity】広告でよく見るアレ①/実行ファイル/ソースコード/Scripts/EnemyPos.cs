//EnemyPosの操作クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyPos : MonoBehaviour
{
    //Enemyプレハブ取得用
    [SerializeField]
    private GameObject enemyPrefab;
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
    //コルーチン止める秒数
    [SerializeField]
    private float stopSecond;

    //PlayerPosに向かう速さ
    private float moveSpeed;
    //Playerオブジェクト
    private GameObject playerPos;
    //GameManagerオブジェクト
    private GameObject gameManager;
    //GameManagerスクリプト
    private GameManager gameManagerScript;
    //EnemyManagerオブジェクト
    private GameObject enemyManager;
    //EnemyManagerスクリプト
    private EnemyManager enemyManagerScript;
    //EnemyAreaオブジェクト
    private GameObject enemyArea;
    //EnemyaAreaスクリプト
    private EnemyArea enemyAreaScript;
    //EnemyWallオブジェクト
    private GameObject enemyWall;
    //EnemyWallスクリプト
    private EnemyWall enemyWallScript;
    //プレハブ生成した時のプレハブの向き
    private Quaternion rotation;
    //プレハブインスタンス用変数
    private GameObject enemyPrefabIns;
    //最初にプレハブ生成する時に一度だけ通すために使う
    private bool InsEnemy;

    //子要素の数
    public int enemyChildNum;
    //デストロイコルーチン終了したか
    public bool DesColFin;
    //プレイヤーとの戦闘でenemyChildNumが0になったら
    public bool IsDead;

    // Start is called before the first frame update
    void Start()
    {
        //各要素参照したり初期化したりする

        moveSpeed = 0.1f;
        playerPos = GameObject.Find("PlayerPos");
        gameManager = GameObject.Find("GameManager");
        gameManagerScript = gameManager.GetComponent<GameManager>();
        enemyManager = GameObject.Find("EnemyManager");
        enemyManagerScript = enemyManager.GetComponent<EnemyManager>();
        enemyArea = GameObject.Find("EnemyArea");
        enemyAreaScript = enemyArea.GetComponent<EnemyArea>();
        enemyWall = GameObject.Find("EnemyWall");
        enemyWallScript = enemyWall.GetComponent<EnemyWall>();
        DesColFin = false;
        InsEnemy = false;
        enemyChildNum = this.transform.childCount;

        //始まるときにEnemyプレハブをenemyNum分生成しておく
        StartCoroutine("EnemyPrefabInstantiate");
    }

    void Update()
    {
        enemyChildNum = this.transform.childCount;

        if(enemyWallScript.IsWallHitPlayer == true)
        {
            transform.position = Vector3.MoveTowards(transform.position, playerPos.transform.position, moveSpeed);
        }

        if(DesColFin == true)
        {
            IsDead = true;
        }
    }

    IEnumerator EnemyPrefabInstantiate()
    {
        for (int nCount = 0; nCount < enemyManagerScript.enemyNum; nCount++)
        {
            //生成
            enemyPrefabIns = Instantiate(enemyPrefab, new Vector3(Random.Range(min, max), InsPosY, Random.Range(this.transform.position.z, this.transform.position.z + max)), rotation);
            //親指定
            enemyPrefabIns.transform.parent = this.gameObject.transform;

            //停止したい秒数指定
            yield return new WaitForSeconds(stopSecond);
        }
    }
}