//アイテムクラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Item : MonoBehaviour
{
    //Playerの子要素がいくつならくっつくか
    [SerializeField]
    private int stikcChildNum;

    //Playerオブジェクト
    protected GameObject playerObj;
    //Playerスクリプト
    protected Player playerScript;
    //Itemのコライダー取得
    private Collider thisCollider;
    //PlayerDiameterとの衝突位置(ワールド座標)
    private Vector3 hitPos = new Vector3(0.0f, 0.0f, 0.0f);

    //Playerにくっつくことができるか
    [System.NonSerialized]
    public bool IsStick = false;
    //hitPosをローカル座標に変換
    [System.NonSerialized]
    public Vector3 localHitPos = new Vector3(0.0f,0.0f,0.0f);
    //Playerに当たったかどうか
    [System.NonSerialized]
    public bool IsHitPlayer = false;


    protected void Start()
    {
        //各要素を参照したり入れたりする

        playerObj = GameObject.Find("Player");
        playerScript = playerObj.GetComponent<Player>();
    }

    void Update()
    {
        if (playerScript.playerChildNum >= stikcChildNum)
        {
            IsStick = true;
        }

        GetlocalHitPos();
    }



    //localHitPos取得関数
    protected void GetlocalHitPos()
    {
        if (IsHitPlayer == true)
        {
            //ワールド座標を取得出来てからローカル座標に変換
            localHitPos = transform.InverseTransformPoint(hitPos);

            IsHitPlayer = false;
        }
    }

    void OnCollisionEnter(Collision collision)
    {
        if (collision.transform.tag == "Player")
        {
            foreach (ContactPoint point in collision.contacts)
            {
                hitPos = point.point;
            }
            IsHitPlayer = true;
        }
    }
}
