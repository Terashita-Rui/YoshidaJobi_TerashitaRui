//switchB制御クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class switchB : MonoBehaviour
{
    private int a = 0;

    public bool bUseB = false;
    public int counter;
    public float moveX;
    public float moveY;
    public float moveZ;

    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public bool GetbUseB()
    {
        return bUseB;
    }

    void OnTriggerEnter(Collider cOther)
    {
        //プレイヤー乗ったら
        if (cOther.gameObject.CompareTag("Player"))
        {
            bUseB = true;
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
