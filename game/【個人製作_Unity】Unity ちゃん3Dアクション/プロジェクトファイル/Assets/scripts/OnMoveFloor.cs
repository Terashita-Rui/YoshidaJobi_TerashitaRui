//MoveFloor制御クラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OnMoveFloor : MonoBehaviour
{
    void OnCollisionEnter(Collision col)
    {
        if (col.gameObject.tag == "MoveFloor")
        {
            //tagがMoveFloorのオブジェクトに乗るとそれが子になる
            transform.SetParent(col.transform);
        }
    }

    void OnCollisionExit(Collision col)
    {
        if (col.gameObject.tag == "MoveFloor")
        {
            //降りると子じゃなくする
            transform.SetParent(null);
        }
    }
}