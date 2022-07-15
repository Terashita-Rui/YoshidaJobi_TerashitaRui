//リザルトシーン管理クラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class ResultManager : MonoBehaviour
{
    //PlayerScale表示UI
    [SerializeField]
    private Text playerScaleUI;

    //オーディオソース
    private AudioSource audioSource;

    void Start()
    {
        // カーソル表示
        Cursor.visible = true;
    }
        void Update()
    {
        playerScaleUI.text = GameManager.scale_m.ToString("0") + "m" + GameManager.scale_cm.ToString("0") + "cm" + GameManager.scale_mm.ToString("0") + "mm";
    }

    public void SelectRetryButton()
    {
        SceneManager.LoadScene("Game");
    }

    public void SelectGoToTitleButton()
    {
        SceneManager.LoadScene("Title");
    }
}
