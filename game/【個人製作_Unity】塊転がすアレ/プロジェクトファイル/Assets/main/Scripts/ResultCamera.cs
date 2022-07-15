//リザルトシーンのカメラ操作クラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResultCamera : MonoBehaviour
{
    //ゲームのカメラから更にどれくらい離すか
    [SerializeField]
    private float distance;

    void Start()
    {

    }

    void Update()
    {
        //カメラの位置をゲームシーンのカメラと合わせる
        this.transform.localPosition = new Vector3(MyCamera.cameraPos.x, MyCamera.cameraPos.y, MyCamera.cameraPos.z * distance);
    }
}
