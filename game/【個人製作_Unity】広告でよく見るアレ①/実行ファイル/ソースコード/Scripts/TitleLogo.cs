//TitleLogoを動かすクラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class TitleLogo : MonoBehaviour
{
    //タイトルロゴの移動速度
    private float moveSpeed;
    //タイトルロゴの停止位置
    private float stopTitleLogo;
    //停止位置まで動いたかどうか
    private bool IsStopTitleLogo;
    //移動に使う
    private RectTransform thisObjectRect;

    void Start()
    {
        //各要素参照したり初期化したりする

        moveSpeed = -0.5f;
        stopTitleLogo = 150.0f;
        IsStopTitleLogo = false;
        thisObjectRect = this.gameObject.GetComponent<RectTransform>();
        thisObjectRect.localPosition = new Vector2(0.0f, 730.0f);
    }

    void Update()
    {
        //停止位置まで移動しきってないなら
        if (IsStopTitleLogo == false)
        {
            thisObjectRect.Translate(0, moveSpeed, 0);
        }

        if (thisObjectRect.localPosition.y <= stopTitleLogo)
        {
            IsStopTitleLogo = true;
        }
    }
}
