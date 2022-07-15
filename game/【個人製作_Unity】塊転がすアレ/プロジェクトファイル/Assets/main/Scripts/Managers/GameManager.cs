//ゲームシーン管理クラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    //ゲーム開始時のカウントダウン表示UI
    [SerializeField]
    private GameObject countDownUI;
    //ゲーム開始時のカウントダウンテキスト
    [SerializeField]
    private Text countDownText;
    //制限時間
    [SerializeField]
    private float gameTimeLimit;
    //制限時間表示UI
    [SerializeField]
    private Text gameTimeLimitText;
    //TimeUP表示UI
    [SerializeField]
    private GameObject timeUPUI;
    //playerScale表示UI
    [SerializeField]
    private Text playerScaleUI;
    //Dashアイコン表示UI
    [SerializeField]
    private GameObject dashIconUI;
    //Dashが使えるかどうかのパネル
    [SerializeField]
    private GameObject dashCTPanel;
    //DashCT表示TextUI
    [SerializeField]
    private Text dashCTTextUI;

    //オーディオソース
    private AudioSource audioSource;
    //ゲーム開始時のカウントダウン
    private float countDownCount = 3;
    //TimeUPを表示しておく時間
    private float displayTimeUp = 0;
    //Playerオブジェクト
    private GameObject playerObj;
    //PlayerScript入れる
    private Player playerScript;
    //PlayerScaleオブジェクト
    private GameObject playerScaleObj;
    //PlayerDiameterスクリプト
    private PlayerScale playerScaleScript;

    //カウントダウンが終了したか
    [System.NonSerialized]
    public bool IsEndCountDown = false;
    //ゲームがタイムアップしたか
    [System.NonSerialized]
    public bool IsTimeUp = false;

    //ItemがPlayerにくっついたときの音
    public AudioClip stackSE;

    //今回のプレイ時の最後の大きさ
    public static float nowPlayScale;
    //playerScaleScript.currentScaleをmに変換していれる
    public static float scale_m;
    //playerScaleScript.currentScaleをcmに変換して入れる
    public static float scale_cm;
    //playerScaleScript.currentScaleをmmに変換して入れる
    public static float scale_mm;
    //ゲームが終了したか
    public static bool IsGameEnd;

    void Start()
    {
        //各要素を参照したり入れたりする

        audioSource = this.transform.GetComponent<AudioSource>();
        playerObj = GameObject.Find("Player");
        playerScript = playerObj.GetComponent<Player>();
        playerScaleObj = GameObject.Find("PlayerScale");
        playerScaleScript = playerScaleObj.GetComponent<PlayerScale>();

        IsGameEnd = false;

        timeUPUI.SetActive(false);

        SaveSystem.Instance.Load();

        // カーソル非表示
        Cursor.visible = false;
    }

    void Update()
    {
        //各数値がfloatでその都合上たまにマイナスになってしまうから絶対値にしてごまかす(本当はよくない)
        //mに変換
        scale_m = Mathf.Floor(Mathf.Abs(playerScaleScript.currentScale));
        //cmに変換
        scale_cm = Mathf.Floor(Mathf.Abs(playerScaleScript.currentScale * 100 % 100));
        //mmに変換
        scale_mm = Mathf.Floor(Mathf.Abs((playerScaleScript.currentScale * 1000 - (scale_m * 1000 + scale_cm * 10))));

        //playerScaleを各単位に変換したものを表示に反映＋その単位を表示
        playerScaleUI.text = scale_m.ToString("0") + "m" + scale_cm.ToString("0") + "cm" + scale_mm.ToString("0") + "mm";

        if (countDownUI != null)
        {
            //DashCT表示
            dashCTTextUI.text = playerScript.dashCT.ToString();
        }

        //制限時間表示
        gameTimeLimitText.text = gameTimeLimit.ToString("0");
        //カウントダウン表示
        countDownText.text = countDownCount.ToString("0");

        if (IsEndCountDown == true)
        {
            //ダッシュが出来る状態なら
            if (playerScript.IsPossibleDash == true)
            {
                //アイコンの上の黒パネルを消す
                dashCTPanel.SetActive(false);
            }
            else
            {
                //アイコンの上に黒パネルを表示
                dashCTPanel.SetActive(true);
            }

            //dashCTが0以下なら
            if (playerScript.dashCT <= 0.0f)
            {
                //CTを表示しなくする
                dashCTTextUI.gameObject.SetActive(false);
            }
            else
            {
                //CT表示
                dashCTTextUI.gameObject.SetActive(true);
            }
            //PlayerにItemがくっついたら
            if(playerScript.IsHitItem == true)
            {
                audioSource.PlayOneShot(stackSE);
            }

            //制限時間が10秒を切ったら
            if (gameTimeLimit <= 10.0f)
            {
                //テキストの色を赤にする
                gameTimeLimitText.color = new Color(255, 0, 0);
            }

            //制限時間が0以下になったら
            if (gameTimeLimit <= 0.0f)
            {
                gameTimeLimit = 0.0f;
                audioSource.Stop();

                //ゲーム終了時の大きさを入れる
                nowPlayScale = playerScaleScript.currentScale;

                IsTimeUp = true;
                timeUPUI.SetActive(true);
                playerScript.IsOperable = false;
            }
        }

        //カウントダウン終わったら
        if (countDownCount <= 0)
        {
            IsEndCountDown = true;
        }
        if (IsEndCountDown == true)
        {
            countDownUI.SetActive(false);
            IsGameEnd = true;
        }
    }

    void FixedUpdate()
    {
        CountUP_and_Down();
    }

    //各時間を足していったり引いていったりする
    void CountUP_and_Down()
    {
        if (IsEndCountDown == true)
        {
            gameTimeLimit -= Time.deltaTime;
        }
        countDownCount -= Time.deltaTime;

        if (gameTimeLimit <= 0)
        {
            displayTimeUp += Time.deltaTime;
        }

        if (displayTimeUp >= 3)
        {
            SceneManager.LoadScene("Result");
        }
    }
}
