//メニュー画面管理クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class MenuManager : MonoBehaviour
{
    //ステージ01クリア王冠
    [SerializeField]
    private GameObject Crown01;
    //ステージ02クリア王冠
    [SerializeField]
    private GameObject Crown02;
    //ステージ03クリア王冠
    [SerializeField]
    private GameObject Crown03;
    //ステージ04クリア王冠
    [SerializeField]
    private GameObject Crown04;

    //ステージ02ボタン
    [SerializeField]
    private Button stage02Button;
    //ステージ03ボタン
    [SerializeField]
    private Button stage03Button;
    //ステージ04ボタン
    [SerializeField]
    private Button stage04Button;

    //ステージ01パネル
    [SerializeField]
    private GameObject stage01Palen;
    //ステージ02パネル
    [SerializeField]
    private GameObject stage02Palen;
    //ステージ03パネル
    [SerializeField]
    private GameObject stage03Palen;
    //ステージ04パネル
    [SerializeField]
    private GameObject stage04Palen;
    //Quitパネル
    [SerializeField]
    private GameObject QuitPanel;
    //Resetパネル
    [SerializeField]
    private GameObject ResetPanel;

    //ステージ01のハイスコアUI
    [SerializeField]
    private Text HighScore01UI;
    //ステージ02のハイスコアUI
    [SerializeField]
    private Text HighScore02UI;
    //ステージ03のハイスコアUI
    [SerializeField]
    private Text HighScore03UI;
    //ステージ04のハイスコアUI
    [SerializeField]
    private Text HighScore04UI;

    //audioSource参照
    private AudioSource audioSource;


    //決定音
    public AudioClip DecisionSE;

    void Start()
    {
        //各要素参照したり初期化したりする

        //メニューを開くとセーブデータをロードする
        SaveSystem.Instance.Load();

        audioSource = GetComponent<AudioSource>();

        Crown01.SetActive(false);
        Crown02.SetActive(false);
        Crown03.SetActive(false);
        Crown04.SetActive(false);

        //各ステージのハイスコアをUIに反映
        HighScore01UI.text = SaveSystem.Instance.UserData.HighScore[0].ToString();
        HighScore02UI.text = SaveSystem.Instance.UserData.HighScore[1].ToString();
        HighScore03UI.text = SaveSystem.Instance.UserData.HighScore[2].ToString();
        HighScore04UI.text = SaveSystem.Instance.UserData.HighScore[3].ToString();

        //ステージ01以外のボタンを使えなくする
        stage02Button.interactable = false;
        stage03Button.interactable = false;
        stage04Button.interactable = false;

        //各ステージをクリアしているなら対応したステージボタンを使えるようにする
        if (SaveSystem.Instance.UserData.StageClear01 == true)
        {
            stage02Button.interactable = true;
        }
        if (SaveSystem.Instance.UserData.StageClear01 == true
         && SaveSystem.Instance.UserData.StageClear02 == true)
        {
            stage03Button.interactable = true;
        }
        if (SaveSystem.Instance.UserData.StageClear01 == true
         && SaveSystem.Instance.UserData.StageClear02 == true
         && SaveSystem.Instance.UserData.StageClear03 == true)
        {
            stage04Button.interactable = true;
        }
    }

    void Update()
    {
        //ステージクリアしていたら各ステージボタンに王冠を付ける
        if(SaveSystem.Instance.UserData.StageClear01 == true)
        {
            Crown01.SetActive(true);
        }
        if (SaveSystem.Instance.UserData.StageClear02 == true)
        {
            Crown02.SetActive(true);
        }
        if (SaveSystem.Instance.UserData.StageClear03 == true)
        {
            Crown03.SetActive(true);
        }
        if (SaveSystem.Instance.UserData.StageClear04 == true)
        {
            Crown04.SetActive(true);
        }
    }

    //そのステージで遊ぶか確認するパネル開くボタン
    public void SelectStageButton(int Num)
    {
        switch (Num)
        {//各ステージで遊ぶか確認パネルを表示しSEを鳴らす
            case 1:
                stage01Palen.SetActive(true);
                audioSource.PlayOneShot(DecisionSE);
                break;
            case 2:
                stage02Palen.SetActive(true);
                audioSource.PlayOneShot(DecisionSE);
                break;
            case 3:
                stage03Palen.SetActive(true);
                audioSource.PlayOneShot(DecisionSE);
                break;
            case 4:
                stage04Palen.SetActive(true);
                audioSource.PlayOneShot(DecisionSE);
                break;
        }
    }

    //押したらステージシーンに遷移するボタン
    public void GoStageBotton(int Num)
    {
        switch (Num)
        {//各ステージに遷移
            case 1:
                audioSource.PlayOneShot(DecisionSE);
                SceneManager.LoadScene("stage01");
                break;
            case 2:
                audioSource.PlayOneShot(DecisionSE);
                SceneManager.LoadScene("stage02");
                break;
            case 3:
                audioSource.PlayOneShot(DecisionSE);
                SceneManager.LoadScene("stage03");
                break;
            case 4:
                audioSource.PlayOneShot(DecisionSE);
                SceneManager.LoadScene("stage04");
                break;
        }
    }

    //押すとパネルを閉じるボタン
    public void ClosePanelButton()
    {
        audioSource.PlayOneShot(DecisionSE);

        stage01Palen.SetActive(false);
        stage02Palen.SetActive(false);
        stage03Palen.SetActive(false);
        stage04Palen.SetActive(false);
        QuitPanel.SetActive(false);
        ResetPanel.SetActive(false);
    }

    //ゲームの終了するか確認するパネル開くボタン
    public void SelectQuitPanelButton()
    {
        audioSource.PlayOneShot(DecisionSE);
        QuitPanel.SetActive(true);
    }

    //ゲームの終了
    public void SelectQuitButton()
    {
        audioSource.PlayOneShot(DecisionSE);

        //終了前に一応セーブしておく
        SaveSystem.Instance.Save();

#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#elif UNITY_STANDALONE
        UnityEngine.Application.Quit();
#endif
    }

    //ゲームの進行状況リセットするか確認するパネル開くボタン
    public void SelectResetPanelButton()
    {
        audioSource.PlayOneShot(DecisionSE);

        ResetPanel.SetActive(true);
    }

    //ゲームの進行状況リセットするボタン
    public void SelectResetButton()
    {
        audioSource.PlayOneShot(DecisionSE);

        //各データリセット
        SaveSystem.Instance.UserData.HighScore[0] = 0;
        SaveSystem.Instance.UserData.HighScore[1] = 0;
        SaveSystem.Instance.UserData.HighScore[2] = 0;
        SaveSystem.Instance.UserData.HighScore[3] = 0;

        SaveSystem.Instance.UserData.StageClear01 = false;
        SaveSystem.Instance.UserData.StageClear02 = false;
        SaveSystem.Instance.UserData.StageClear03 = false;
        SaveSystem.Instance.UserData.StageClear04 = false;

        //データ書き換えたのでセーブ
        SaveSystem.Instance.Save();

        //タイトルに戻る
        SceneManager.LoadScene("Title");
    }
}
