//ハイスコアを更新したときにゲームのセーブをするクラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameSave : MonoBehaviour
{
    //Goalオブジェクト
    private GameObject goal;
    //Goalスクリプト
    private Goal goalScript;
    //PlayerManagerオブジェクト
    private GameObject playerManager;
    //PlayerManagerスクリプト
    private PlayerManager playerManagerScript;

    //ハイスコア更新したら
    public bool[] GetHigeScoer;

    void Start()
    {
        //各要素参照したり初期化したりする

        goal = GameObject.Find("Goal");
        goalScript = goal.GetComponent<Goal>();
        playerManager = GameObject.Find("PlayerManager");
        playerManagerScript = playerManager.GetComponent<PlayerManager>();

        //ステージ数の分だけ回す
        for (int nCnt = 0; nCnt < 4; nCnt++)
        {
            GetHigeScoer[nCnt] = false;
        }
       
    }

    void Update()
    {
        if (goalScript.IsGoal == true)
        {
            //保存してあるハイスコアよりもいいスコアを取ったら更新
            if (SceneManager.GetActiveScene().name == "stage01")
            {
                if (SaveSystem.Instance.UserData.HighScore[0] < playerManagerScript.HighScore)
                {
                    SaveSystem.Instance.UserData.HighScore[0] = playerManagerScript.HighScore;
                    GetHigeScoer[0] = true;
                    SaveSystem.Instance.Save();
                }
            }
            if (SceneManager.GetActiveScene().name == "stage02")
            {
                if (SaveSystem.Instance.UserData.HighScore[1] < playerManagerScript.HighScore)
                {
                    SaveSystem.Instance.UserData.HighScore[1] = playerManagerScript.HighScore;
                    GetHigeScoer[1] = true;
                    SaveSystem.Instance.Save();
                }
            }
            if (SceneManager.GetActiveScene().name == "stage03")
            {
                if (SaveSystem.Instance.UserData.HighScore[2] < playerManagerScript.HighScore)
                {
                    SaveSystem.Instance.UserData.HighScore[2] = playerManagerScript.HighScore;
                    GetHigeScoer[2] = true;
                    SaveSystem.Instance.Save();
                }
            }
            if (SceneManager.GetActiveScene().name == "stage04")
            {
                if (SaveSystem.Instance.UserData.HighScore[3] < playerManagerScript.HighScore)
                {
                    SaveSystem.Instance.UserData.HighScore[3] = playerManagerScript.HighScore;
                    GetHigeScoer[3] = true;
                    SaveSystem.Instance.Save();
                }
            }
        }

    }
}
