//EnemyWall制御クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyWall : MonoBehaviour
{

    //Playerが当たったかどうか
    public bool IsWallHitPlayer;

    void Start()
    {
        //各要素参照したり初期化したりする

        IsWallHitPlayer = false;
    }

    private void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.tag == "PlayerPos")
        {
            IsWallHitPlayer = true;
        }
    }
}
