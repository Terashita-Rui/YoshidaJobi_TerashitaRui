//PlayerPrefab動かすクラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class PlayerMove : MonoBehaviour
{
    //追尾対象
    private GameObject chaseTarget;
    //ナビメッシュエージェント参照
    private NavMeshAgent navMeshAgent;
    //PlayerManagerオブジェクト
    private GameObject playerManagerObj;
    //PlayerManagerスクリプト
    private PlayerManager playerManagerScript;
    //アニメーターコントローラー
    private CharacterController characterController;
    //アニメーター
    private Animator animator;

    void Start()
    {
        //各要素参照したり初期化したりする

        chaseTarget = GameObject.Find("PlayerPos");
        navMeshAgent = GetComponent<NavMeshAgent>();
        playerManagerObj = GameObject.Find("PlayerManager");
        playerManagerScript = playerManagerObj.GetComponent<PlayerManager>();
        characterController = this.gameObject.GetComponent<CharacterController>();
        animator = this.gameObject.GetComponent<Animator>();
    }

    void Update()
    {
        if(playerManagerScript.IsIdleMotion == true)
        {
            animator.SetTrigger("Idle");
        }
        if (playerManagerScript.IsRunMotion == true)
        {
            animator.SetTrigger("Run");
        }
        if (playerManagerScript.IsUdehuriMotion == true)
        {
            animator.SetTrigger("Udehuri");
        }
        if (playerManagerScript.IsYorokobiMotion == true)
        {
            animator.SetTrigger("Yorokobi");
        }

        //PlayerPosを目指して進む
        navMeshAgent.destination =  new Vector3(chaseTarget.transform.position.x,this.transform.position.y, chaseTarget.transform.position.z);

        //向きをchaseTargetと合わせる
        this.gameObject.transform.rotation = chaseTarget.transform.rotation;
    }

    public void OnTriggerEnter(Collider collision)
    {
        if(collision.gameObject.tag == "Goal")
        {
            playerManagerScript.IsYorokobiMotion = true;
        }
    }
}
