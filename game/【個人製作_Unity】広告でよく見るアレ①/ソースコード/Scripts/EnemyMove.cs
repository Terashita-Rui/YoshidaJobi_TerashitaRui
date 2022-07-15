//EnemyPrefabの移動処理クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnemyMove : MonoBehaviour
{
    //EnemyPosオブジェクト
    private GameObject enemyPos;
    //ナビメッシュエージェント
    private NavMeshAgent navMeshAgent;
    //PlayerManagerオブジェクト
    private GameObject enemyManagerObj;
    //PlayerManagerスクリプト
    private EnemyManager enemyManagerScript;
    //EnemyWallオブジェクト
    private GameObject enemyWall;
    //EnemyWallスクリプト
    private EnemyWall enemyWallScript;
    //アニメーターコントローラー
    private CharacterController characterController;
    //アニメーター
    private Animator animator;

    void Start()
    {
        //各要素参照したり初期化したりする

        enemyPos = GameObject.Find("EnemyPos");
        navMeshAgent = GetComponent<NavMeshAgent>();
        enemyManagerObj = GameObject.Find("EnemyManager");
        enemyManagerScript = enemyManagerObj.GetComponent<EnemyManager>();
        enemyWall = GameObject.Find("EnemyWall");
        enemyWallScript = enemyWall.GetComponent<EnemyWall>();
        characterController = this.gameObject.GetComponent<CharacterController>();
        animator = this.gameObject.GetComponent<Animator>();
    }

    void Update()
    {
        //各モーションを実行
        if (enemyManagerScript.IsIdleMotion == true)
        {
            animator.SetTrigger("Idle");
        }
        if (enemyManagerScript.IsRunMotion == true)
        {
            animator.SetTrigger("Run");
        }
        if (enemyManagerScript.IsUdehuriMotion == true)
        {
            animator.SetTrigger("Udehuri");
        }
        if (enemyManagerScript.IsYorokobiMotion == true)
        {
            animator.SetTrigger("Yorokobi");
        }

        navMeshAgent.destination = enemyPos.transform.position;

        //向きをchaseTargetと合わせる
        this.gameObject.transform.rotation = enemyPos.transform.rotation;

        if (enemyWallScript.IsWallHitPlayer == true)
        {
            enemyManagerScript.IsRunMotion = true;
        }
    }

}