//Playerにくっついた子要素を合わせた大きさを出すクラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerScale : MonoBehaviour
{
    //拡大していく速さ
    [SerializeField]
    private float addExpansionSpeed;
    //スフィアとカプセルコライダーの中心をどれくらい動かすか
    [SerializeField]
    private float moveCenter;

    //Playerオブジェクト
    private GameObject playerObj;
    //Playerスクリプト
    private Player playerScript;
    //Itemスクリプト(Itemに当たったら取得するからStartでは何もしない)
    private Item itemScript;
    //スフィアコライダー
    private SphereCollider sphereCollider;
    //Playerに子要素が無いときの大きさ(一番最初の大きさ)
    private float firstScale;
    //Playerと子要素を合わせた大きさ
    private float playerScale;
    //lastChildObjのCenterを動かしてもいいか
    private bool IsMoveCenter = false;
    //playerScript.IsHitItemがtrueになったら各Itemにつき一度だけIsMoveCenterをtrueにするための変数
    private bool IsHitItemTrue = false;

    //現在の大きさ
    [System.NonSerialized]
    public float currentScale;
    //PlayerにくっついたItemとPlayerとの距離
    [System.NonSerialized]
    public float stackScale;
    //当たったオブジェクトの要素を消していいか
    [System.NonSerialized]
    public bool IsDestroy = false;

    void Start()
    {
        //各要素を参照したり入れたりする

        playerObj = GameObject.Find("Player");
        playerScript = playerObj.GetComponent<Player>();
        sphereCollider = this.GetComponent<SphereCollider>();

        firstScale = sphereCollider.radius * 2;
        playerScale = firstScale;
        currentScale = firstScale;
    }

    void Update()
    {
        //Playerの子にするとPlayerChildNumに引っかかるので、子要素にしないで位置を揃える
        this.transform.position = playerObj.transform.position;
        //回転も一応揃える
        this.transform.rotation = playerObj.transform.rotation;

        //現在の直径と更新している直径を比べる
        if (currentScale < playerScale)
        {
            //大きい方に合わせる
            currentScale = playerScale;
        }

        //PlayerがItemに当たったら
        if (playerScript.IsHitItem == true)
        {
            MoveObjectCenter();

            //Itemに当たるまで大きくしていく
            sphereCollider.radius += addExpansionSpeed;

            if (IsHitItemTrue == false)
            {
                sphereCollider.isTrigger = true;
                IsMoveCenter = true;
                IsHitItemTrue = true;
            }
        }
        if (playerScript.IsHitItem == false)
        {
            //当たったら最初の状態に戻す
            sphereCollider.radius = firstScale / 2;
        }
        if (playerScript.IsAboutPlayerScale == true)
        {
            addExpansionSpeed = addExpansionSpeed + 0.03f;
        }
    }

    //Playerが当たったオブジェクトの中心をずらす関数
    void MoveObjectCenter()
    {
        //lastChildObjがあるなら
        if (playerScript.lastChildObj != null)
        {
            //PlayerScriptのitemScriptに中身があるなら
            if (playerScript.itemScript != null)
            {
                if (IsMoveCenter == true)
                {
                    //lastChildObjのコライダーがSphereColliderなら
                    if (playerScript.lastChildObj.GetComponent<SphereCollider>() != null)
                    {
                        Vector3 hitLocalPos = playerScript.itemScript.localHitPos;

                        //コライダーの半径の分だけ各方向にずらす
                        if (hitLocalPos.x > 0.0f)
                        {

                            playerScript.lastChildObj.GetComponent<SphereCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<SphereCollider>().center.x - playerScript.lastChildObj.GetComponent<SphereCollider>().radius, playerScript.lastChildObj.GetComponent<SphereCollider>().center.y, playerScript.lastChildObj.GetComponent<SphereCollider>().center.z);
                        }
                        else if (hitLocalPos.x < 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<SphereCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<SphereCollider>().center.x + playerScript.lastChildObj.GetComponent<SphereCollider>().radius, playerScript.lastChildObj.GetComponent<SphereCollider>().center.y, playerScript.lastChildObj.GetComponent<SphereCollider>().center.z);
                        }
                        if (hitLocalPos.y > 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<SphereCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<SphereCollider>().center.x, playerScript.lastChildObj.GetComponent<SphereCollider>().center.y - playerScript.lastChildObj.GetComponent<SphereCollider>().radius, playerScript.lastChildObj.GetComponent<SphereCollider>().center.z);
                        }
                        else if (hitLocalPos.y < 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<SphereCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<SphereCollider>().center.x, playerScript.lastChildObj.GetComponent<SphereCollider>().center.y + playerScript.lastChildObj.GetComponent<SphereCollider>().radius, playerScript.lastChildObj.GetComponent<SphereCollider>().center.z);
                        }
                        if (hitLocalPos.z > 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<SphereCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<SphereCollider>().center.x, playerScript.lastChildObj.GetComponent<SphereCollider>().center.y, playerScript.lastChildObj.GetComponent<SphereCollider>().center.z - playerScript.lastChildObj.GetComponent<SphereCollider>().radius);
                        }
                        else if (hitLocalPos.z < 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<SphereCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<SphereCollider>().center.x, playerScript.lastChildObj.GetComponent<SphereCollider>().center.y, playerScript.lastChildObj.GetComponent<SphereCollider>().center.z + playerScript.lastChildObj.GetComponent<SphereCollider>().radius);
                        }
                    }
                    //lastChildObjのコライダーがBoxColliderなら
                    else if (playerScript.lastChildObj.GetComponent<BoxCollider>() != null)
                    {
                        Vector3 hitLocalPos = playerScript.itemScript.localHitPos;

                        //コライダーのサイズの分だけ各方向にずらす
                        if (hitLocalPos.x > 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<BoxCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<BoxCollider>().center.x - playerScript.lastChildObj.GetComponent<BoxCollider>().size.x, playerScript.lastChildObj.GetComponent<BoxCollider>().center.y, playerScript.lastChildObj.GetComponent<BoxCollider>().center.z);
                        }
                        else if (hitLocalPos.x < 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<BoxCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<BoxCollider>().center.x + playerScript.lastChildObj.GetComponent<BoxCollider>().size.x, playerScript.lastChildObj.GetComponent<BoxCollider>().center.y, playerScript.lastChildObj.GetComponent<BoxCollider>().center.z);
                        }
                        if (hitLocalPos.y > 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<BoxCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<BoxCollider>().center.x, playerScript.lastChildObj.GetComponent<BoxCollider>().center.y - playerScript.lastChildObj.GetComponent<BoxCollider>().size.y, playerScript.lastChildObj.GetComponent<BoxCollider>().center.z);
                        }
                        else if (hitLocalPos.y < 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<BoxCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<BoxCollider>().center.x, playerScript.lastChildObj.GetComponent<BoxCollider>().center.y + playerScript.lastChildObj.GetComponent<BoxCollider>().size.y, playerScript.lastChildObj.GetComponent<BoxCollider>().center.z);
                        }
                        if (hitLocalPos.z > 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<BoxCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<BoxCollider>().center.x, playerScript.lastChildObj.GetComponent<BoxCollider>().center.y, playerScript.lastChildObj.GetComponent<BoxCollider>().center.z - playerScript.lastChildObj.GetComponent<BoxCollider>().size.z);
                        }
                        else if (hitLocalPos.z < 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<BoxCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<BoxCollider>().center.x, playerScript.lastChildObj.GetComponent<BoxCollider>().center.y, playerScript.lastChildObj.GetComponent<BoxCollider>().center.z + playerScript.lastChildObj.GetComponent<BoxCollider>().size.z);
                        }
                    }
                    //lastChildObjのコライダーがCapsuleColliderなら
                    else if (playerScript.lastChildObj.GetComponent<CapsuleCollider>() != null)
                    {
                        Vector3 hitLocalPos = playerScript.itemScript.localHitPos;

                        //コライダーの半径の分だけ各方向にずらす
                        if (hitLocalPos.x > 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<CapsuleCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.x - playerScript.lastChildObj.GetComponent<CapsuleCollider>().radius, playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.y, playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.z);
                        }
                        else if (hitLocalPos.x < 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<CapsuleCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.x + playerScript.lastChildObj.GetComponent<CapsuleCollider>().radius, playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.y, playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.z);
                        }
                        if (hitLocalPos.y > 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<CapsuleCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.x, playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.y - playerScript.lastChildObj.GetComponent<CapsuleCollider>().radius, playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.z);
                        }
                        else if (hitLocalPos.y < 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<CapsuleCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.x, playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.y + playerScript.lastChildObj.GetComponent<CapsuleCollider>().radius, playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.z);
                        }
                        if (hitLocalPos.z > 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<CapsuleCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.x, playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.y, playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.z - playerScript.lastChildObj.GetComponent<CapsuleCollider>().radius);
                        }
                        else if (hitLocalPos.z < 0.0f)
                        {
                            playerScript.lastChildObj.GetComponent<CapsuleCollider>().center
                                = new Vector3(playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.x, playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.y, playerScript.lastChildObj.GetComponent<CapsuleCollider>().center.z + playerScript.lastChildObj.GetComponent<CapsuleCollider>().radius);
                        }
                    }

                    //複数回通らないようにする
                    IsMoveCenter = false;
                }
            }
        }
    }

    //すり抜けてもなんとなくの直径取れるようにStay
    void OnTriggerStay(Collider collider)
    {
        if (collider.transform.gameObject == playerScript.lastChildObj)
        {
            Debug.Log("当たった");

            IsDestroy = true;

            //stackScaleを求めてから10000倍して必要な部分までを整数にして、いらない部分の少数点を切り捨ててから少数に戻す
            stackScale = Mathf.Floor((sphereCollider.radius - playerObj.GetComponent<SphereCollider>().radius) * 10000) / 10000;
            //Playerの子要素を含めた大きさ = 最初の大きさ + (大きくなったコライダーの半径 - 最初の半径)
            playerScale = firstScale + (sphereCollider.radius - (firstScale / 2));

            IsHitItemTrue = false;
            sphereCollider.isTrigger = false;
            playerScript.IsHitItem = false;
        }
    }
}