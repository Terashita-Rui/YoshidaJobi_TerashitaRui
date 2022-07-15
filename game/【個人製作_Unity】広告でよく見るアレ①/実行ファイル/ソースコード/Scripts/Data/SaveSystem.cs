//セーブやロードのシステムクラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class SaveSystem
{
    #region Singleton
    private static SaveSystem instance = new SaveSystem();
    public static SaveSystem Instance => instance;
    #endregion

    //このインスタンスを作った時にデータのロードをする
    private SaveSystem() { Load(); }

    //保存先の定義
    public string Path => Application.dataPath + "/data.json";
    public UserData UserData { get; private set; }

    //セーブデータの書き込み
    public void Save()
    {
        //各要素参照したり初期化したりする

        string jsonData = JsonUtility.ToJson(UserData);

        //ファイルの上書き
        StreamWriter writer = new StreamWriter(Path, false);

        //書き残しがあれば無理やり書き出し
        writer.WriteLine(jsonData);
        writer.Flush();
        writer.Close();
    }

    //セーブデータの読み込み
    public void Load()
    {
        //セーブデータが無いなら
        if(!File.Exists(Path))
        {
            //データの初期化
            UserData = new UserData();
            //セーブデータファイルを作成
            Save();
            return;
        }

        //読み込むファイル指定
        StreamReader reader = new StreamReader(Path);
        //指定したファイル読み込み
        string jsonData = reader.ReadToEnd();
        UserData = JsonUtility.FromJson<UserData>(jsonData);

        //ファイルを閉じる
        reader.Close();
    }
}
