//アイテムを往復運動させるクラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move : MonoBehaviour
{
    //縦移動
    [SerializeField]
    private bool IsVertical = false;
    //横移動
    [SerializeField]
    private bool IsHorizontal = false;

    //移動速度
    private float moveSpeed;
    //往復する時の片道にかける時間
    private float oneWayTime;
    //往復していいか
    private bool IsTurn = false;
    //MoveTurnを実行してもいいか
    private bool IsMoveTurn = true;

    void Start()
    {

    }

    void Update()
    {

        if(this.transform.parent.name != "Item")
        {
            IsMoveTurn = false;
        }

        if(IsMoveTurn == true)
        {
            MoveTrue();
        }
    }

    void MoveTrue()
    {
        oneWayTime -= Time.deltaTime;

        if (oneWayTime <= 0.0f)
        {
            if (IsTurn == true)
            {
                IsTurn = false;
                oneWayTime = 2.0f;
            }
            else if (IsTurn == false)
            {
                IsTurn = true;
                oneWayTime = 2.0f;
            }
        }

        if (IsHorizontal == true)
        {
            if (IsTurn == true)
            {
                this.transform.position = new Vector3(this.transform.position.x, this.transform.position.y, this.transform.position.z + 0.1f);
            }
            else if (IsTurn == false)
            {
                this.transform.position = new Vector3(this.transform.position.x, this.transform.position.y, this.transform.position.z - 0.1f);
            }
        }
        if(IsVertical == true)
        {
            if (IsTurn == true)
            {
                this.transform.position = new Vector3(this.transform.position.x + 0.1f, this.transform.position.y, this.transform.position.z);
            }
            else if (IsTurn == false)
            {
                this.transform.position = new Vector3(this.transform.position.x - 0.1f, this.transform.position.y, this.transform.position.z);
            }
        }
    }
}
