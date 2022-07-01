//メニュー画面のスカイボックス変更クラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeSykBox : MonoBehaviour
{
    //変更先のスカイボックス
    [SerializeField]
    private Material[] changeSkyBox;
    //乱数の最大(インスペクターでchangeSkyBoxのサイズと同じ値にする)
    [SerializeField]
    private int max;


    //乱数の最小値
    private int min = 0;
    //生成した乱数を入れる
    private int random;
    //スカイボックスを変更したかどうか
    private bool IsChangeSkyBox;

    void Start()
    {
        //各要素参照したり初期化したりする

        //シード値
        Random.InitState(System.DateTime.Now.Millisecond);

        //各要素参照したり初期化したりする
        IsChangeSkyBox = false;
    }

    void Update()
    {
        random = Random.Range(min, max);

        if (IsChangeSkyBox == false)
        {
            for (int nCnt = 0; nCnt <= max; nCnt++)
            {
                if (random == nCnt)
                {
                    RenderSettings.skybox = changeSkyBox[nCnt];
                }
            }

            IsChangeSkyBox = true;
        }
    }
}
