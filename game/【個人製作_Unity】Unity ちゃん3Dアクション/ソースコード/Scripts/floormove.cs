//移動する床制御クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class floormove : MonoBehaviour
{

    //片道の移動にかける時間
    public int counter = 0;
    //各移動速度
    public float moveX = 0.0f;
    public float moveY = 0.0f;
    public float moveZ = 0.0f;


    void Update()
    {
        //各moveを入れる
        Vector3 p = new Vector3(moveX, moveY, moveZ);
        //各moveを入れたVectorを移動させる
        transform.Translate(p);

        //往復させるために使う
        int a = 0;

        a++;

        if (a == counter)
        {
            //逆方向に動かす(往復に入る)
            moveX *= -1;
            moveY *= -1;
            moveZ *= -1;

            //
            a = 0;
        }
    }
}