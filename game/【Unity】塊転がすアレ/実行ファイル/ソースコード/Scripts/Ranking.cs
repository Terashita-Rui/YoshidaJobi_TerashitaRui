//ランキング制御クラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Ranking : MonoBehaviour
{
    //ランキングの順位テキスト
    [SerializeField]
    private Text[] rankingText = new Text[10];

    //ランキングの更新が終わったか
    private bool IsEndUpdataRanking = false;
    //をmに変換していれる
    private float scale_m;
    //をcmに変換して入れる
    private float scale_cm;
    //をmmに変換して入れる
    private float scale_mm;

    void Start()
    {

    }

    void Update()
    {
        if (IsEndUpdataRanking == false)
        {
            //ランキングが10位まで表示なので、ランキングで使わない配列の11個目に今回の大きさ(スコア)を入れる
            SaveSystem.Instance.UserData.highScore[SaveSystem.Instance.UserData.highScore.Length - 1] = GameManager.nowPlayDiameter;

            //今回のスコア＋保存してあるスコアでバブルソートする
            BubbleSort(SaveSystem.Instance.UserData.highScore);

            for (int nCnt = 0; nCnt < SaveSystem.Instance.UserData.highScore.Length - 1; nCnt++)
            {
                //ソートしたスコアを各単位に変換
                //mに変換
                scale_m = Mathf.Floor(Mathf.Abs(SaveSystem.Instance.UserData.highScore[nCnt]));
                //cmに変換
                scale_cm = Mathf.Floor(Mathf.Abs(Mathf.Abs(SaveSystem.Instance.UserData.highScore[nCnt] * 100 % 100)));
                //mmに変換
                scale_mm = Mathf.Floor(Mathf.Abs((Mathf.Abs(SaveSystem.Instance.UserData.highScore[nCnt] * 1000 - (scale_m * 1000 + scale_cm * 10)))));

                //順位とスコアをテキストに入れる
                rankingText[nCnt].text = nCnt + 1 + "位 : " + scale_m.ToString("0") + "m" + scale_cm.ToString("0") + "cm" + scale_mm.ToString("0") + "mm";
            }

            SaveSystem.Instance.Save();

            IsEndUpdataRanking = true;
        }

    }

    //渡されたスコアでバブルソードする関数
   void BubbleSort(float[] score)
    {
        //配列の回数分回す
        for (int nCnt0 = 0; nCnt0 < score.Length; nCnt0++)
        {
            //配列の回数分回す
            for (int nCnt1 = nCnt0 + 1; nCnt1 < score.Length; nCnt1++)
            {
                //比較元より大きければ入れ替え
                if (score[nCnt0] < score[nCnt1])
                {
                    float x = score[nCnt1];
                    score[nCnt1] = score[nCnt0];
                    score[nCnt0] = x;
                }
            }
        }
    }
}