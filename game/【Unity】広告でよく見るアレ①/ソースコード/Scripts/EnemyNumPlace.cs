//EnemyAreaの上に出してるEnemyの数の管理

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyNumPlace : MonoBehaviour
{
    //0～9のマテリアル
    [SerializeField]
    private Material[] NumMaterial;

    //GameManager
    private GameObject gameManager;
    //EnemyPos参照
    private GameObject enemyPos;
    //EnemyPosスクリプト参照
    private EnemyPos enemyPosScript;
    //GameManagerスクリプト参照
    private GameManager gameManagerScript;
    //GameManagerのGEnemyNumの百の位の数字を取得
    private int HundredPlaceNum;
    //GameManagerのGEnemyNumの百の位の数字を取得
    private int TenthPlaceNum;
    //GameManagerのGEnemyNumの百の位の数字を取得
    private int FirstPlaceNum;


    void Start()
    {
        //各要素参照したり初期化したりする

        gameManager = GameObject.Find("GameManager");
        gameManagerScript = gameManager.GetComponent<GameManager>();
        enemyPos = GameObject.Find("EnemyPos");
        enemyPosScript = enemyPos.GetComponent<EnemyPos>();

    }

    void Update()
    {
        if (enemyPosScript.DesColFin == false)
        {
            //〇の位の数取得
            HundredPlaceNum = gameManagerScript.GEnemyNum / 100;
            TenthPlaceNum = (gameManagerScript.GEnemyNum / 10) % 10;
            FirstPlaceNum = gameManagerScript.GEnemyNum % 10;

            for (int nCount = 0; nCount <= 10; nCount++)
            {
                if (this.gameObject.transform.name == "HundredPlace")
                {
                    //百の位が0なら
                    if (HundredPlaceNum == 0)
                    {
                        this.gameObject.SetActive(false);
                    }
                    if (HundredPlaceNum == nCount)
                    {
                        //マテリアル変更
                        this.GetComponent<Renderer>().material = NumMaterial[nCount];
                    }
                }
                if (this.gameObject.transform.name == "TenthPlace")
                {
                    //百の位と十の位が0なら
                    if (HundredPlaceNum == 0
                    && TenthPlaceNum == 0)
                    {
                       this.gameObject.SetActive(false);
                    }
                    if (TenthPlaceNum == nCount)
                    {
                        //マテリアル変更
                        this.GetComponent<Renderer>().material = NumMaterial[nCount];
                    }
                }
                if (this.gameObject.transform.name == "FirstPlace")
                {
                    if (FirstPlaceNum == nCount)
                    {
                        //マテリアル変更
                        this.GetComponent<Renderer>().material = NumMaterial[nCount];
                    }
                }
            }
        }
    }
}
