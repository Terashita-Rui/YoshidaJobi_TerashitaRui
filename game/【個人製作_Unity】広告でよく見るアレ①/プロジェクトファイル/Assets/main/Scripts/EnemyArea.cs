//EnemyAreaにPlayerが当たったらどうするかの処理クラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyArea : MonoBehaviour
{
    //EnemyPosオブジェクト
    [SerializeField]
    private GameObject enemyPos;

    //EnemyPosスクリプト
    private EnemyPos enemyPosScript;


    void Start()
    {
        //各要素参照したり初期化したりする

        enemyPosScript = enemyPos.GetComponent<EnemyPos>();

        //EnemyPosをEnemyAreaの中心に置く
        this.gameObject.transform.position = enemyPos.transform.position;
    }
}
