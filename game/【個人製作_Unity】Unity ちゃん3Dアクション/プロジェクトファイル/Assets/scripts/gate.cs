//スイッチ押したら上に上がる門の制御クラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class gate : MonoBehaviour
{
    //各オブジェクトそのものを入れる変数
    GameObject SwitchA;
    GameObject SwitchB;

    //各スクリプトを入れる
    switchA SA;
    switchB SB;

    public bool bUseA; //UseAの情報を取得
    public bool bUseB; //UseBの情報を取得

    //floormoveと使い方同じ
    public int counter;
    public float moveX;
    public float moveY;
    public float moveZ;

    void Start()
    {
        //オブジェクトの情報を変数に格納
        SwitchA = GameObject.Find("switchA");
        SwitchB = GameObject.Find("switchB");

        //スクリプト取得
        SA = SwitchA.GetComponent<switchA>();
        SB = SwitchB.GetComponent<switchB>();
    }

    // Update is called once per frame
    void Update()
    {
        bUseA = SA.GetbUseA();
        bUseB = SB.GetbUseB();

        Vector3 p = new Vector3(moveX, moveY, moveZ);

        //両方のボタンが押されたら
        if(bUseA == true && bUseB == true)
        {
               int a = 0;
            transform.Translate(p);
            a++;

            if (a == counter)
            {
                //一定以上移動したら止める
                moveX = 0;
                moveY = 0;
                moveZ = 0;
            }
        }
    }
}
