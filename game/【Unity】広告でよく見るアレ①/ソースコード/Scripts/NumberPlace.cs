//gateに表示している数字の管理クラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NumberPlace : MonoBehaviour
{
    //0～9のマテリアル
    [SerializeField]
    private Material[] NumMaterial;

    //Gate参照
    private GameObject gate;
    //Gateスクリプト参照
    private Gate gateScript;
    //Codeオブジェクト
    private GameObject CodeObj;
    //HundredPlaceオブジェクト
    private GameObject HundredPlaceObj;
    //TenthPlaceオブジェクト
    private GameObject TenthPlaceObj;
    //FirstPlaceオブジェクト
    private GameObject FirstPlaceObj;
    //GateのaddPlayerNumの百の位の数字を取得
    private int HundredPlaceNum;
    //GateのaddPlayerNumの十の位の数字を取得
    private int TenthPlaceNum;
    //GateのaddPlayerNumの一の位の数字を取得
    private int FirstPlaceNum;

    void Start()
    {
        //各要素参照したり初期化したりする

        gate = transform.root.gameObject;
        gateScript = gate.GetComponent<Gate>();

        //〇の位取得
        HundredPlaceNum = gateScript.addPlayerNum / 100;
        TenthPlaceNum = (gateScript.addPlayerNum / 10) % 10;
        FirstPlaceNum = gateScript.addPlayerNum % 10;

        //addPlayerNumに応じたマテリアルになるようにする
        for (int nCount = 0; nCount <= 10; nCount++)
        {
            if(this.gameObject.transform.name == "HundredPlace")
            {
                //百の位が0なら
                if(HundredPlaceNum == 0)
                {
                    this.gameObject.SetActive(false);
                }
                if (HundredPlaceNum == nCount)
                {
                    this.GetComponent<Renderer>().material = NumMaterial[nCount];
                }
            }
            if (this.gameObject.transform.name == "TenthPlace")
            {
                //百の位と十の位が0なら
                if(HundredPlaceNum == 0
                && TenthPlaceNum == 0)
                {
                    this.gameObject.SetActive(false);
                }
                if (TenthPlaceNum == nCount)
                {
                    this.GetComponent<Renderer>().material = NumMaterial[nCount];
                }
            }
            if (this.gameObject.transform.name == "FirstPlace")
            {
                if (FirstPlaceNum == nCount)
                {
                    this.GetComponent<Renderer>().material = NumMaterial[nCount];
                }
            }
        }
    }
}

