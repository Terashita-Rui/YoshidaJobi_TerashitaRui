//メインカメラ操作クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainCamera : MonoBehaviour
{
    //PlayerPos参照
    [SerializeField]
    private GameObject playerPos;
    //カメラのpos調整
    [SerializeField]
    private Vector3 cameraPos;

    void Update()
    {
        //PlayerPosの子要素にしないでカメラをPlayerPosに追従するようにする
        this.transform.position = new Vector3(playerPos.transform.position.x + cameraPos.x,
                                              playerPos.transform.position.y + cameraPos.y,
                                              playerPos.transform.position.z + cameraPos.z);
    }
}
