//保存しておきたいデータを格納するクラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class UserData
{
    //ステージ毎のハイスコア更新用
    public int[] HighScore = { 0,0,0,0,0 };

    //各ステージクリアフラグ
    public bool StageClear01 = false;
    public bool StageClear02 = false;
    public bool StageClear03 = false;
    public bool StageClear04 = false;
}
