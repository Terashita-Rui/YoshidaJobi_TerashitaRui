//ゲームスタートボタン制御クラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class titlebutton : MonoBehaviour
{
    void Start()
    {
        Invoke("Update", 1.5f);

    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Application.LoadLevel("tutorial");
        }
    }
}
