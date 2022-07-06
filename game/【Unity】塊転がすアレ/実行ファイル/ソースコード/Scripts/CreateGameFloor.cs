//floorを自動生成するクラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CreateGameFloor : MonoBehaviour
{
    //生成するfloorオブジェクトプレハブ
    [SerializeField]
    private GameObject floorPrefab;

    //生成したオブジェクトを入れる
    private GameObject createObj;
    //一列のfloorを作る数
    private int floorNum = 10;
    //複数回通らないようにする
    private bool IsCompleted = false;

    void Update()
    {
        if (IsCompleted == false)
        {
            for (int nCnt0 = 0; nCnt0 < floorNum; nCnt0++)
            {
                for (int nCnt1 = 0; nCnt1 < floorNum; nCnt1++)
                {
                    //床オブジェクト生成
                    createObj = Instantiate(floorPrefab, new Vector3(-135.0f + (30 * nCnt0), 0.0f, -135.0f + (30 * nCnt1)), Quaternion.identity);

                    //createObjの親を設定
                    createObj.transform.parent = this.transform;
                }
            }

            IsCompleted = true;
        }
    }
}
