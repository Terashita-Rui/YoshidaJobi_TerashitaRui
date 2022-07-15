//Goal管理クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Goal : MonoBehaviour
{
    //ゴールしたかどうか
    public bool IsGoal = false;

    private void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.tag == "Player")
        {
            IsGoal = true;
        }

        //各ステージをクリアしたらクリアフラグを立てる
        if (SceneManager.GetActiveScene().name == "stage01")
        {
            SaveSystem.Instance.UserData.StageClear01 = true;
        }
        if (SceneManager.GetActiveScene().name == "stage02")
        {
            SaveSystem.Instance.UserData.StageClear02 = true;
        }
        if (SceneManager.GetActiveScene().name == "stage03")
        {
            SaveSystem.Instance.UserData.StageClear03 = true;
        }
        if (SceneManager.GetActiveScene().name == "stage04")
        {
            SaveSystem.Instance.UserData.StageClear04 = true;
        }
    }
}
