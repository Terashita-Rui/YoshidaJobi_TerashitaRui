//ゲームシーンのUI管理クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class UIManager : MonoBehaviour
{
    //GPlayerNumを表示しておくUI
    [SerializeField]
    private Text playerNumUI;
    //ハイスコア更新したときに表示するUI
    [SerializeField]
    private GameObject UpdateHigeScroerUI;
    //リスタートボタン
    [SerializeField]
    private GameObject RestartButton;
    //メニューに戻るボタン
    [SerializeField]
    private GameObject GoMenuButton;

    //GameManagerオブジェクト
    private GameObject gameManager;
    //GameManagerスクリプト
    private GameManager gameManagerScript;
    //PlayerManagerオブジェクト
    private GameObject playerManager;
    //PlayerManagerスクリプト
    private PlayerManager playerManagerScript;
    //PlayerPosオブジェクト
    private GameObject playerPos;
    //PlayerPosスクリプト
    private PlayerPos playerPosScript;
    //Goalオブジェクト
    private GameObject goal;
    //Goalスクリプト
    private Goal goalScript;
    //SaveManagerオブジェクト
    private GameObject saveManager;
    //GameSaveスクリプト
    private GameSave gameSaveScript;
    //UpdateHigeScroerUIを表示しておく時間
    private float activeHighScroreUITime;

    void Start()
    {
        //各要素参照したり初期化したりする

        gameManager = GameObject.Find("GameManager");
        gameManagerScript = gameManager.GetComponent<GameManager>();
        playerManager = GameObject.Find("PlayerManager");
        playerManagerScript = playerManager.GetComponent<PlayerManager>();
        playerPos = GameObject.Find("PlayerPos");
        playerPosScript = playerPos.GetComponent<PlayerPos>();
        goal = GameObject.Find("Goal");
        goalScript = goal.GetComponent<Goal>();
        saveManager = GameObject.Find("SaveManager");
        gameSaveScript = saveManager.GetComponent<GameSave>();
        UpdateHigeScroerUI.SetActive(false);
        RestartButton.SetActive(false);
        GoMenuButton.SetActive(false);
        activeHighScroreUITime = 0.0f;
    }

    void Update()
    {
        SetPlayerNumText();
        SetActiveButton();

        activeHighScroreUITime += Time.deltaTime;

        //各ステージでハイスコアを出した時にUpdateHigeScroerUIを点滅させる
        if (SceneManager.GetActiveScene().name == "stage01")
        {
            if (gameSaveScript.GetHigeScoer[0]
         && activeHighScroreUITime >= 1.0f)
            {
                UpdateHigeScroerUI.SetActive(true);

                if (activeHighScroreUITime >= 2.0f)
                {
                    UpdateHigeScroerUI.SetActive(false);
                    activeHighScroreUITime = 0.0f;
                }
            }
        }
        else if (SceneManager.GetActiveScene().name == "stage02")
        {
            if (gameSaveScript.GetHigeScoer[1]
         && activeHighScroreUITime >= 1.0f)
            {
                UpdateHigeScroerUI.SetActive(true);

                if (activeHighScroreUITime >= 2.0f)
                {
                    UpdateHigeScroerUI.SetActive(false);
                    activeHighScroreUITime = 0.0f;
                }
            }
        }
        else if (SceneManager.GetActiveScene().name == "stage03")
        {
            if (gameSaveScript.GetHigeScoer[2]
         && activeHighScroreUITime >= 1.0f)
            {
                UpdateHigeScroerUI.SetActive(true);

                if (activeHighScroreUITime >= 2.0f)
                {
                    UpdateHigeScroerUI.SetActive(false);
                    activeHighScroreUITime = 0.0f;
                }
            }
        }
        else if (SceneManager.GetActiveScene().name == "stage04")
        {
            if (gameSaveScript.GetHigeScoer[3]
         && activeHighScroreUITime >= 1.0f)
            {
                UpdateHigeScroerUI.SetActive(true);

                if (activeHighScroreUITime >= 2.0f)
                {
                    UpdateHigeScroerUI.SetActive(false);
                    activeHighScroreUITime = 0.0f;
                }
            }
        }
    }

    //プレイヤーの数UIを操作する
    private void SetPlayerNumText()
    {
        playerNumUI.text = playerManagerScript.playerPrefabNum.ToString();

        if (playerManagerScript.playerPrefabNum == 0)
        {
            //プレイヤーの数が0になったらplayerNumUIを赤くする
            playerNumUI.color = new Color(255, 0, 0);
        }
        else
        {
            //0以外なら白
            playerNumUI.color = new Color(255, 255, 255);
        }
    }

    //各ボタンを有効にする
    private void SetActiveButton()
    {
        if (playerPosScript.IsinGate == true)
        {
            //ゲート通ってからにしないと遷移した瞬間にボタンが表示されるから必ずゲート通ってからにする
            if (playerPosScript.playerChildNum <= 0)
            {
                //playerChildNumが0になったらやり直すボタンをメニューに戻るボタンを表示
                RestartButton.SetActive(true);
                GoMenuButton.SetActive(true);

            }
        }
        if(gameManagerScript.IsDead == true
        || playerPosScript.IsDead == true)
        {
            //Enemyと戦ってplayerChildNumが0になったら
            RestartButton.SetActive(true);
            GoMenuButton.SetActive(true);
        }
        if (goalScript.IsGoal == true)
        {
            //ゴールしたらやり直すボタンをメニューに戻るボタンを表示
            RestartButton.SetActive(true);
            GoMenuButton.SetActive(true);
        }
    }

    //やり直すボタン押したら
    public void SelectRestartButton()
    {
        //やり直すボタンを押したら各シーンを初めから実行
        if (SceneManager.GetActiveScene().name == "stage01")
        {
            SceneManager.LoadScene("stage01");
        }
        if (SceneManager.GetActiveScene().name == "stage02")
        {
            SceneManager.LoadScene("stage02");
        }
        if (SceneManager.GetActiveScene().name == "stage03")
        {
            SceneManager.LoadScene("stage03");
        }
        if (SceneManager.GetActiveScene().name == "stage04")
        {
            SceneManager.LoadScene("stage04");
        }

    }

    //メニューに戻るボタン押したら
    public void SelectGoMenuButton()
    {
        SceneManager.LoadScene("Menu");
    }
}
