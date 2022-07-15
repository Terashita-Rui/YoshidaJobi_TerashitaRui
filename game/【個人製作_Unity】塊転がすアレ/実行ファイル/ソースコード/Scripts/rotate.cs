//Itemを回せるようにするクラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class rotate : MonoBehaviour
{
    //回転方向プラスにする
    [SerializeField]
    private bool IsRotatePlus = false;
    //回転方向マイナスにする
    [SerializeField]
    private bool IsRotateMinus = false;
    //回転方向Xにする
    [SerializeField]
    private bool IsRotateX = false;
    //回転方向Yにする
    [SerializeField]
    private bool IsRotateY = false;
    //回転方向Zにする
    [SerializeField]
    private bool IsRotateZ = false;
    //回転速度
    [SerializeField]
    private float rotateSpeed = 0.0f;


    void Update()
    {
        //親が無いか親の名前がItemなら
        if (this.gameObject.transform.parent == null
            || this.gameObject.transform.parent.name == "Item")
        {
            if (IsRotatePlus == true)
            {
                if (IsRotateX == true)
                {
                    this.gameObject.transform.Rotate(new Vector3(rotateSpeed, 0.0f, 0.0f));
                }
                if (IsRotateY == true)
                {
                    this.gameObject.transform.Rotate(new Vector3(0.0f, rotateSpeed, 0.0f));
                }
                if (IsRotateZ == true)
                {
                    this.gameObject.transform.Rotate(new Vector3(0.0f, 0.0f, rotateSpeed));
                }
            }
            else if (IsRotatePlus == true)
            {
                if (IsRotateX == true)
                {
                    this.gameObject.transform.Rotate(new Vector3(-rotateSpeed, 0.0f, 0.0f));
                }
                if (IsRotateY == true)
                {
                    this.gameObject.transform.Rotate(new Vector3(0.0f, -rotateSpeed, 0.0f));
                }
                if (IsRotateZ == true)
                {
                    this.gameObject.transform.Rotate(new Vector3(0.0f, 0.0f, -rotateSpeed));
                }
            }
        }
    }
}

