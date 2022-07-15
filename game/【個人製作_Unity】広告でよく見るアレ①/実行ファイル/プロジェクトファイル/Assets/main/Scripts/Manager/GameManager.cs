//ゲームの管理クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    //BlackPanelオブジェクト
    [SerializeField]
    private GameObject blackPanel;

    //EnemyWallオブジェクト
    private GameObject enemyWall;
    //EnemyWallスクリプト
    private EnemyWall enemyWallScript;
    //PlayerManagerオブジェクト
    private GameObject playerManager;
    //PlayerManagerスクリプト
    private PlayerManager playerManagerScript;
    //EnemyManagerオブジェクト
    private GameObject enemyManager;
    //EnemyManagerスクリプト
    private EnemyManager enemyManagerScript;
    //PlayerPosオブジェクト
    private GameObject playerPos;
    //PlayerPosスクリプト
    private PlayerPos playerPosScript;
    //EnemyPosオブジェクト
    private GameObject enemyPos;
    //EnemyPosスクリプト
    private EnemyPos enemyPosScript;
    //EnemyAriaオブジェクト
    private GameObject enemyArea;
    //EnemyAriaスクリプト
    private EnemyArea enemyAreaScript;

    //一旦GPlayerNumを保存しておく
    private int GkeepPlayerNum;
    //一旦GEnemyNumを保存しておく
    private int GkeepEnemyNum;
    //audioSource参照
    private AudioSource audioSource;
    //ReusePlayerNumSEを鳴らす間隔
    private float ReusePlayerNumSECoolTime;

    //PlayerNumを保存しておく(インスペクターでさわるな)
    public int GPlayerNum;
    //EnemyNumを保存しておく(インスペクターでさわるな)
    public int GEnemyNum;
    //なにかキーを押したかどうか
    public bool IsAnykey;
    //playerChildNumがPlayerDestroyによって0になったかどうか
    public bool IsDead;
    //戦闘中かどうか
    public bool IsBattle;
    //PlayerNumが減ったら鳴らす
    public AudioClip ReusePlayerNumSE;

    void Start()
    {
        //各要素参照したり初期化したりする

        enemyWall = GameObject.Find("EnemyWall");
        enemyWallScript = enemyWall.GetComponent<EnemyWall>();
        playerManager = GameObject.Find("PlayerManager");
        playerManagerScript = playerManager.GetComponent<PlayerManager>();
        enemyManager = GameObject.Find("EnemyManager");
        enemyManagerScript = enemyManager.GetComponent<EnemyManager>();
        playerPos = GameObject.Find("PlayerPos");
        playerPosScript = playerPos.GetComponent<PlayerPos>();
        enemyPos = GameObject.Find("EnemyPos");
        enemyPosScript = enemyPos.GetComponent<EnemyPos>();
        enemyArea = GameObject.Find("EnemyArea");
        enemyAreaScript = enemyArea.GetComponent<EnemyArea>();
        audioSource = GetComponent<AudioSource>();
        ReusePlayerNumSECoolTime = 0.0f;

        blackPanel.SetActive(true);

        GPlayerNum = playerManagerScript.playerNum;
        GEnemyNum = enemyManagerScript.enemyNum;
        IsAnykey = false;
        IsDead = false;
        IsBattle = false;

    }

    void Update()
    {
        ReusePlayerNumSECoolTime += Time.deltaTime;

        if (Input.anyKey)
        {//何かキーを押したら
            //モーション切り替え
            playerManagerScript.IsIdleMotion = false;
            playerManagerScript.IsRunMotion = true;
            //黒パネル消す
            blackPanel.SetActive(false);
            IsAnykey = true;
        }
        if (playerPosScript.InsColFin == false
        || playerPosScript.DesColFin == false)
        {//どちらかのコルーチンが終わったら
            //playerNumとGPlayerNumの数を合わせる
            GPlayerNum = playerManagerScript.playerNum;
        }
        if (enemyPosScript.DesColFin == false)
        {//Enemy消すコルーチン終わったら
            //enemyNumとGEnemyNumの数を合わせる
            GEnemyNum = enemyManagerScript.enemyNum;
        }
        if (playerPosScript.DesColFin == true
        && enemyPosScript.DesColFin == true)
        {
            playerPosScript.IsHitEnemyPos = false;
        }
        if (playerPosScript.IsHitEnemyPos == true)
        {
            //各コルーチンスタート
            StartCoroutine("PlayerDestroy");
            StartCoroutine("EnemyDestroy");
        }
        if (playerPosScript.IsgoalPos == true)
        {
            //モーション切り替え
            playerManagerScript.IsRunMotion = false;
            playerManagerScript.IsYorokobiMotion = true;
        }
        if (playerPosScript.IsHitEnemyPos == true)
        {
            //モーション切り替え
            playerManagerScript.IsRunMotion = false;
            playerManagerScript.IsUdehuriMotion = false;
            playerManagerScript.IsUdehuriMotion = true;
            enemyManagerScript.IsUdehuriMotion = true;
        }
        if (enemyWallScript.IsWallHitPlayer == true)
        {
            enemyManagerScript.IsRunMotion = true;
        }
    }

    IEnumerator PlayerDestroy()
    {
        //GkeepEnemyNumでforを回すから現在のGEnemyNumを保存しておく
        GkeepEnemyNum = GEnemyNum;

        if (playerPosScript.IsHitEnemyPos == true)
        {
            for (int nCount = 0; nCount < GkeepEnemyNum; nCount++)
            {
                //一定間隔でSE鳴らす
                if (ReusePlayerNumSECoolTime >= 0.5f)
                {
                    audioSource.PlayOneShot(ReusePlayerNumSE);

                    //CTを0にしておく
                    ReusePlayerNumSECoolTime = 0.0f;
                }
                if (playerPosScript.playerChildNum <= 0)
                {
                    //playerChildNumが0以下になったら各要素を設定する
                    enemyManagerScript.IsYorokobiMotion = true;
                    IsDead = true;
                    playerManagerScript.playerPrefabNum = playerPosScript.playerChildNum;
                    playerPosScript.DesColFin = true;

                    yield break;
                }
                if (enemyPosScript.enemyChildNum <= 0)
                {
                    //enemyChildNumが0以下になったら各要素を設定する
                    playerManagerScript.playerPrefabNum = playerPosScript.playerChildNum;
                    playerPosScript.DesColFin = true;

                    yield break;
                }

                Destroy(playerPos.transform.GetChild(0).gameObject);
                //持っている子要素の数を変えたのでPlayerManagerScriptのplayerPrefabNumを子要素の数に合わせる
                playerManagerScript.playerPrefabNum = playerPosScript.playerChildNum;

                yield return null;
            }
        }
        //デストロイコルーチン終了
        playerPosScript.DesColFin = true;
    }

    IEnumerator EnemyDestroy()
    {
        //GkeepPlayerNumでforを回すから現在のGPlayerNumを保存しておく
        GkeepPlayerNum = GPlayerNum;

        if (playerPosScript.IsHitEnemyPos == true)
        {
            for (int nCount = 0; nCount < GkeepPlayerNum; nCount++)
            {
                if (enemyPosScript.enemyChildNum <= 0)
                {
                    //enemyChildNumが0以下になったら各要素を設定する
                    enemyManagerScript.enemyNum = enemyPosScript.enemyChildNum;
                    enemyWallScript.IsWallHitPlayer = false;
                    enemyPosScript.DesColFin = true;
                    playerPosScript.IsHitEnemyPos = false;

                    yield break;
                }
                if (playerPosScript.playerChildNum <= 0)
                {
                    //playerChildNumが0以下になったら各要素を設定する
                    enemyManagerScript.enemyNum = enemyPosScript.enemyChildNum;
                    enemyPosScript.DesColFin = true;
                    playerPosScript.IsHitEnemyPos = false;

                    yield break;
                }

                Destroy(enemyPos.transform.GetChild(0).gameObject);
                //持っている子要素の数を変えたので各変数を子要素の数に合わせる
                enemyManagerScript.enemyNum = enemyPosScript.enemyChildNum;

                yield return null;
            }
        }
        //デストロイコルーチン終了
        enemyPosScript.DesColFin = true;
        playerManagerScript.IsRunMotion = true;
    }
}
