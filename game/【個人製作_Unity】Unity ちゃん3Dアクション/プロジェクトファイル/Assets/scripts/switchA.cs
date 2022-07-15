//switchA制御クラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class switchA : MonoBehaviour
{
    private int a = 0;

    public bool bUseA = false;
    public int counter;
    public float moveX;
    public float moveY;
    public float moveZ;

    public bool GetbUseA()
    {
        return bUseA;
    }

    void OnTriggerEnter(Collider cOther)
    {
        //プレイヤー乗ったら
        if (cOther.gameObject.CompareTag("Player"))
        {
            bUseA = true;
            Vector3 p = new Vector3(moveX, moveY, moveZ);
            transform.Translate(p);
            a++;

            if (a == counter)
            {
                moveX = 0;
                moveY = 0;
                moveZ = 0;
            }
        }
    }
}