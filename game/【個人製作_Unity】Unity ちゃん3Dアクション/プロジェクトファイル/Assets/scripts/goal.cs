//ゴールクラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class goal : MonoBehaviour
{
    void Start()
    {
        //マウスカーソル非表示
        Cursor.visible = false;
    }


    void OnTriggerEnter(Collider cOther)
    {
        //操作キャラが当たったら
        if(cOther.gameObject.CompareTag("Player"))
        {
            //シーンの名前取得してその名前なら
            if(SceneManager.GetActiveScene().name == "tutorial")
            {
                //次のシーンに移動
                SceneManager.LoadScene("Game0");
            }

            if(SceneManager.GetActiveScene().name == "Game0")
            {
                SceneManager.LoadScene("Game1");
            }

            if (SceneManager.GetActiveScene().name == "Game1")
            {
                SceneManager.LoadScene("Game2");
            }

            if (SceneManager.GetActiveScene().name == "Game2")
            {
                SceneManager.LoadScene("end");
            }
        }
    }
}

