//マウスでカメラ操作出来るようにするクラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyCamera : MonoBehaviour
{
    //プレイヤーオブジェクト入れる
    [SerializeField]
    private GameObject player;
    //MainCamera入れる
    [SerializeField]
    private Camera camera;
    //カメラの回転スピード
    [SerializeField]
    private float rotateSpeed = 3;
    //Axisの位置を指定する変数
    [SerializeField]
    private Vector3 axisPos;
    //Updataでカメラを離すときにどれくらい離すか
    [SerializeField]
    private float updataCameraDistance;

    //最初にカメラをどれくらい離すか
    private float cameraDistance = -20.0f;
    //Playerオブジェクト参照
    private GameObject playerObj;
    //Playerスクリプト
    private Player playerScript;
    //X軸の角度を制限するための変数
    private float angleUp = 60f;
    private float angleDown = -60f;
    //カメラを離すかどうか
    private bool IsCameraDistance = false;

    //カメラPos(リザルトシーンに渡すのでstatic)
    public static Vector3 cameraPos;

    void Start()
    {
        playerObj = GameObject.Find("Player");
        playerScript = playerObj.GetComponent<Player>();
        //引きたいからマイナスをかける

        //CameraのAxisに相対的な位置をlocalPositionで指定
        camera.transform.localPosition = new Vector3(0, 0, -3);
        //CameraとAxisの向きを最初だけそろえる
        camera.transform.localRotation = transform.rotation;

        //Cameraの位置
        camera.transform.localPosition
            = new Vector3(camera.transform.localPosition.x,
            camera.transform.localPosition.y,
            camera.transform.localPosition.z + cameraDistance);
    }

    void Update()
    {
        cameraPos = camera.transform.localPosition;

        //Axisの位置をプレイヤー位置＋axisPosで決める
        transform.position = player.transform.position + axisPos;

        if (IsCameraDistance == true)
        {
            //カメラを離す
            camera.transform.localPosition
               = new Vector3(camera.transform.localPosition.x,
               camera.transform.localPosition.y,
               camera.transform.localPosition.z + updataCameraDistance);

            IsCameraDistance = false;
        }
    
        //Cameraの角度にマウスからとった値を入れる
        transform.eulerAngles += new Vector3(
           0,
            Input.GetAxis("Mouse X") * rotateSpeed
            , 0);

        //X軸の角度
        float angleX = transform.eulerAngles.x;
        //X軸の値を180度超えたら360引くことで制限しやすくする
        if (angleX >= 180)
        {
            angleX = angleX - 360;
        }
        //Mathf.Clamp(値、最小値、最大値）でX軸の値を制限する
        transform.eulerAngles = new Vector3(
            Mathf.Clamp(angleX, angleDown, angleUp),
            transform.eulerAngles.y,
            transform.eulerAngles.z
        );

        if(playerScript.IsAboutPlayerDiameter == true)
        {
           IsCameraDistance = true;

           playerScript.IsAboutPlayerDiameter = false;
        }
    }
}
