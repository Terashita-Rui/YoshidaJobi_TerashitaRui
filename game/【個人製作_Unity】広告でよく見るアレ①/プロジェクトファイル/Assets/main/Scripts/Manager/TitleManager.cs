//メニュー画面の管理クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class TitleManager : MonoBehaviour
{
    //PressAnyKeyロゴ
    [SerializeField]
    private GameObject pressAnyKeyUI;

    //pressAnyKeyUIを表示しておく時間
    private float activePressAnyKeyUI;

    void Start()
    {
        //各要素参照したり初期化したりする

        pressAnyKeyUI.SetActive(true);
    }

        void Update()
    {
        activePressAnyKeyUI += Time.deltaTime;



        if (Input.anyKey == true)
        {
            //なにかキーを押したらメニューに遷移
            SceneManager.LoadScene("Menu");
        }

        //activePressAnyKeyUIを点滅させる
        if (activePressAnyKeyUI >= 1.0f)
        {
            pressAnyKeyUI.SetActive(false);

            if (activePressAnyKeyUI >= 2.0f)
            {
                pressAnyKeyUI.SetActive(true);

                activePressAnyKeyUI = 0.0f;
            }
        }
    }
}
