//エネミーの管理クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyManager : MonoBehaviour
{
    //EnemyPosオブジェクト
    private GameObject enemyPos;
    //EnemyPosスクリプト
    private EnemyPos enemyPosScript;
    //EnemyAreaオブジェクト
    private GameObject enemyArea;
    //EnemyaAreaスクリプト
    private EnemyArea enemyAreaScript;

    //最初に生成するEnemyプレハブの数兼現在のEnemyプレハブの数
    public int enemyNum;
    //計算につかうEnemyプレハブの数
    public int enemyPrefabNum;
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

        enemyPos = GameObject.Find("EnemyPos");
        enemyPosScript = enemyPos.GetComponent<EnemyPos>();
        enemyArea = GameObject.Find("EnemyArea");
        enemyAreaScript = enemyArea.GetComponent<EnemyArea>();

        enemyPrefabNum = enemyPosScript.enemyChildNum;

        IsIdleMotion = true;
        IsRunMotion = false;
        IsUdehuriMotion = false;
        IsYorokobiMotion = false;
    }

    void Update()
    {
        //プレハブの数をEnemyPosの子要素の数と同じ表示にする
        enemyPrefabNum = enemyPosScript.enemyChildNum;

        if (enemyPosScript.DesColFin == true)
        {
            //エネミーの数を減らすコルーチンが終わったenemyNumとenemyPrefabNumを揃える
            enemyNum = enemyPrefabNum;
            enemyPosScript.DesColFin = false;
        }
    }
}
