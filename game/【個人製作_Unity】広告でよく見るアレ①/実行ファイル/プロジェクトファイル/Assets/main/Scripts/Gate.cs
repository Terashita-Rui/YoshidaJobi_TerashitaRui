//Gate制御クラス
//Auther:寺下琉生

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gate : MonoBehaviour
{
    //PlusGateマテリアル
    [SerializeField]
    private Material plusMaterial;
    //MinusGateマテリアル
    [SerializeField]
    private Material minusMaterial;
    //MultiplicationGateマテリアル
    [SerializeField]
    private Material multiplicationMaterial;

    //通った時にどの計算でPlayerの数を変えるか
    public enum GateType
    {
        none,               //通常
        plus,               //足し算
        minus,              //引き算
        multiplication,     //掛け算
    }

    //通ったPlayerの数を変える時の右辺になる数字
    public int addPlayerNum;
    //GateType管理
    public GateType gateType;

    void Start()
    {
        //各要素参照したり初期化したりする

        //自身が何ゲートのタグを持っているかによってマテリアルとGateTypeを自動で変更
        if (gameObject.tag == "PlusGate")
        {
            this.GetComponent<Renderer>().material = plusMaterial;
            gateType = GateType.plus;
        }
        else if (gameObject.tag == "MinusGate")
        {
            this.GetComponent<Renderer>().material = minusMaterial;
            gateType = GateType.minus;
        }
        else if (gameObject.tag == "MultiplicationGate")
        {
            this.GetComponent<Renderer>().material = multiplicationMaterial;
            gateType = GateType.multiplication;
        }
    }

    //どのゲートを通ったのか返す
    public GateType GetGateType()
    {
        return gateType;
    }
}
