//タイトルシーン管理クラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class TitleManager : MonoBehaviour
{
    //GameQuitPanel
    [SerializeField]
    private GameObject gameQuitPanel;
    //オーディオソース
    private AudioSource audioSource;

    //決定音
    public AudioClip decisionSE;

    void Start()
    {
        gameQuitPanel.SetActive(false);
        audioSource = this.transform.GetComponent<AudioSource>();
        // カーソル表示
        Cursor.visible = true;
    }

    void Update()
    {

    }

    //ゲームスタートボタン
    public void SelectGameStartButton()
    {
        audioSource.PlayOneShot(decisionSE);
        SceneManager.LoadScene("Game");
    }

    //終了確認パネル表示ボタン
    public void SelectQuitPanelButton()
    {
        audioSource.PlayOneShot(decisionSE);

        //GameQuitPanelをアクティブにする
        gameQuitPanel.SetActive(true);
    }

    //終了確認パネルのやめておくボタン
    public void SelectCloseQuitPanelButton()
    {
        audioSource.PlayOneShot(decisionSE);

        gameQuitPanel.SetActive(false);
    }

    //終了確認パネルの終了ボタン
    public void SelectQuitGameButton()
    {
        audioSource.PlayOneShot(decisionSE);

#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#elif UNITY_STANDALONE
        UnityEngine.Application.Quit();
#endif
    }
}
