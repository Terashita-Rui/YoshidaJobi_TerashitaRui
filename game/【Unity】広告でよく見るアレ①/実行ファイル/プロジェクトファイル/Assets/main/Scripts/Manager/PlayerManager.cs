//プレイヤーの管理クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PlayerManager : MonoBehaviour
{
    //EnemyAreaオブジェクト
    private GameObject enemyArea;
    //EnemyAreaスクリプト
    private EnemyArea enemyAreaScript;
    //GameManagerオブジェクト
    private GameObject gameManager;
    //GameManagerスクリプト
    private GameManager gameMagaerScript;
    //PlayerPosオブジェクト
    private GameObject playerPos;
    //PlayerPosMoveスクリプト
    private PlayerPos playerPosScript;
    //Goalオブジェクト
    private GameObject goal;
    //Goalスクリプト
    private Goal goalScript;
    //Gateスクリプト(Gateに当たったら取得するのでStartでは何もしない)
    private Gate gateScript;

    //一旦プレイヤーの数を保持する変数
    public int playerNum;
    //Playerプレハブの数
    public int playerPrefabNum;
    //ハイスコア更新用
    public int HighScore;
    //Idleモーションをするかどうか
    public bool IsIdleMotion;
    //Runモーションをするかどうか
    public bool IsRunMotion;
    //Udehuriモーションをするかどうか
    public bool IsUdehuriMotion;
    //Yorokobiモーションをするかどうか
    public bool IsYorokobiMotion;

    void Start()
    {
        //各要素参照したり初期化したりする

        gameManager = GameObject.Find("GameManager");
        gameMagaerScript = gameManager.GetComponent<GameManager>();
        enemyArea = GameObject.Find("EnemyArea");
        enemyAreaScript = enemyArea.GetComponent<EnemyArea>();
        playerPos = GameObject.Find("PlayerPos");
        playerPosScript = playerPos.GetComponent<PlayerPos>();
        goal = GameObject.Find("Goal");
        goalScript = goal.GetComponent<Goal>();
        playerPrefabNum = 1;
        playerNum = playerPrefabNum;
        IsIdleMotion = true;
        IsRunMotion = false;
        IsUdehuriMotion = false;
        IsYorokobiMotion = false;
    }

    void Update()
    {
        //プレハブの数をPlayerPosの子要素の数と同じにする
        playerPrefabNum = playerPosScript.playerChildNum;

        if (goalScript.IsGoal == true)
        {
            //ゲームクリア時にセーブしてあるハイスコアよりもいいスコアを取ったらスコア更新するのでとりあえず今取ったスコアをハイスコアに入れる
            HighScore = playerPrefabNum;
        }

        if (playerPosScript.InsColFin == true)
        {
            //プレハブを増やすコルーチンが終わったのでplayerNumとplayerPrefabNumを揃える
            playerNum = playerPrefabNum;
            playerPosScript.InsColFin = false;
        }
        else if (playerPosScript.DesColFin == true)
        {
            //プレハブを減らすコルーチンが終わったのでplayerNumとplayerPrefabNumを揃える
            playerNum = playerPrefabNum;
            playerPosScript.DesColFin = false;
        }
    }

    void PlusGate()
    {
        //playerPrefabNumとaddPlayerNumの数を足す
        playerNum = playerPrefabNum + gateScript.addPlayerNum;
    }

    void MinusGate()
    {
        //playerPrefabNumとaddPlayerNumの数を引く
        playerNum = playerPrefabNum - gateScript.addPlayerNum;
    }

    void MultiplicationGate()
    {
        //playerPrefabNumとaddPlayerNumの数をかける
        playerNum = playerPrefabNum * gateScript.addPlayerNum;
    }

    private void OnTriggerEnter(Collider collider)
    {
        //いずれかのゲートを通ったら
        if (collider.gameObject.tag == "PlusGate"
            || collider.gameObject.tag == "MinusGate"
            || collider.gameObject.tag == "MultiplicationGate")
        {
            //通ったゲートのスクリプトを取得
            gateScript = collider.GetComponent<Gate>();

            //各ゲートに対応した関数を呼び出し
            if (playerPosScript.IsinGate == true)
            {
                if (gateScript.GetGateType() == Gate.GateType.plus)
                {
                    PlusGate();
                }
                else if (gateScript.GetGateType() == Gate.GateType.minus)
                {
                    MinusGate();
                }
                else if (gateScript.GetGateType() == Gate.GateType.multiplication)
                {
                    MultiplicationGate();
                }
            }

            if (playerPosScript.InsColFin == true)
            {
                //コルーチンが終わったのでplayerNumとplayerPrefabNumを揃える
                playerNum = playerPrefabNum;
            }

            else if (playerPosScript.DesColFin == true)
            {
                //コルーチンが終わったのでplayerNumとplayerPrefabNumを揃える
                playerNum = playerPrefabNum;
            }
        }
    }
}