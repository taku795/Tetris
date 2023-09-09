#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <conio.h>


#define field_h 22
#define field_w 12

//ミノの形を定義
int mino[7][4][4][4]={
    //一個目
    {
        {
            {1,0,0,0},
            {1,0,0,0},
            {1,0,0,0},
            {1,0,0,0}
        },
        {
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}
        },
        {
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
    },
    //2個目
    {
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
    },
    //3個目
    {
        {
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,0,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,0,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
    },
    //4個目
    {
        {
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {1,1,0,0},
            {1,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {1,1,0,0},
            {1,0,0,0},
            {0,0,0,0}
        },
    },
    //5個目
    {
        {
            {1,0,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {1,0,0,0},
            {1,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,1,0},
            {0,0,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {1,1,0,0},
            {0,0,0,0}
        },
    },
    //6個目
    {
        {
            {0,0,1,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,0,0,0},
            {1,0,0,0},
            {1,1,0,0},
            {0,0,0,0}
        },
        {
            {1,1,1,0},
            {1,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
    },
    //7個目
    {
        {
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {1,0,0,0},
            {1,1,0,0},
            {1,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,1,0},
            {0,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
    },

};


int field[22][12];
int disbuf[22][12]={};
int mino_x,mino_y;
int shape,angle;

//338行までmain内で使う関数定義

//hitしてたら1を返す
int hit () {
    int i,j;

    for (i=0;i<=3;i++) {
        for (j=0;j<=3;j++) {
            if ((field[mino_y+i][mino_x+j]==1) && (mino[shape][angle][i][j]==1)) {
            return 1;
            }
        }
    }
    return 0;
}

//ミノをフィールドに固定
void mino_fix_on_field () {
    int i,j;

    for (i=0;i<=3;i++) {
        for (j=0;j<=3;j++) {
            field[mino_y+i][mino_x+j]+=mino[shape][angle][i][j];
        }
    }
}

//ミノの位置を初期化して形を決める
void mino_decide (void) {
    srand((int)time(NULL));
    shape=(rand()%10000)%7;
    angle=rand()%4;
    mino_x=5;
    mino_y=1;
}

//ミノをdisbufにコピー
void mino_copy_disbuf (void) {
    int i,j;
    for (i=0;i<4;i++) {
        for (j=0;j<4;j++) {
            disbuf[mino_y+i][mino_x+j]+=mino[shape][angle][i][j];
        }
        
    }
}

//fieldをdisbufにコピー
void field_copy_disbuf (void) {
    int i,j;
    for (i=0;i<field_h;i++) {
        for (j=0;j<field_w;j++) {
            disbuf[i][j]+=field[i][j];
        }
    }
}

//回転させる
void rotate (void) {
    if (angle==3) {
        angle=0;
    } else {
        angle++;
    }
    if (hit()==1) {
        if (angle==0) {
            angle=3;
        } else {
            angle--;
        }
    }
}

//dis初期化
void initialize_disbuf (void) {
    int i,j;
    for (i=0;i<field_h;i++) {
            for (j=0;j<field_w;j++) {
                disbuf[i][j]=0;
            }
        }
}

//disbuf出力
void disbuf_out (void) {
    int i,j;

    system("cls");
        for (i=0;i<field_h;i++) {
            for (j=0;j<field_w;j++) {
                if (disbuf[i][j]==1 || disbuf[i][j]==2) {
                    printf ("■");
                } else {
                    printf("□");
                }
            }
            printf ("\n");
        }
}

//フィールドをチェックしてもし一列揃っていたら消す
void field_cheack_and_delet_one_rine (void) {
    int i,j,k,count=0;

    for (i=field_h-2;i>=1;i--) {
        for (j=1;j<field_w-1;j++) {
        if (field[i][j]==1) {
            count++;
         } else {
            count=0;
        }

        }
        if (count>=10) {
            count=0;
            for (k=i;k>=2;k--) {
                for (j=1;j<field_w-1;j++) {
                    field[k][j]=field[k-1][j];
                    field[k-1][j]=0;
                }
            }
            i++;
        }
    }
}

int main (void)
{
    //i,jはforで使う用
    int i,j;
    time_t t;
    t=time(NULL);

    //外枠定義//
    for (i=0;i<field_h;i++) {
        for (j=0;j<field_w;j++) {
            field[i][0]=1;
            field[i][field_w-1]=1;
            field[0][j]=1;
            field[field_h-1][j]=1;
        }
    }

    //ミノの位置を初期化して形を決める
    mino_decide();

    while (1)
    {
        //dis初期化
        initialize_disbuf();

        //ミノをずらす
        if (_kbhit())
        {
            switch (getch())
            {
                case 'a':
                    mino_x--;
                    if (hit()==1) {
                        mino_x++;
                    }
                break;
                case 's':
                    //借りでミノを動かす
                    mino_y++;
                    if (hit()==1) {
                        //当たったからミノを戻す
                        mino_y--;
                        //ミノをフィールドに固定
                        mino_fix_on_field();
                        //フィールドをチェックしてもし一行揃ってたら消す
                        field_cheack_and_delet_one_rine();
                        //ミノの位置を初期化して形を決める
                        mino_decide();
                    }
                break;
                case 'd':
                    //借りでミノを動かす
                    mino_x++;
                    if (hit()==1) {
                        //当たったらミノを戻す
                        mino_x--;
                        }
                break;
                case 0x20:
                    //回転
                    rotate();
                break;               
                default:
                //何もしない
                break;
            }
            //ミノコピー
            mino_copy_disbuf();
            //fieldコピー
            field_copy_disbuf();
            
            //dis出力
            disbuf_out();

            //2以上がないか判定することで上に当たっていないか確認、当たっていたら終了
            for (i=0;i<field_h;i++) {
                for (j=0;j<field_w;j++) {
                    if (disbuf[i][j]>=2) {
                        return 0;
                    }
                }
            }
            
            //dis初期化
            initialize_disbuf();

        }//ボタンが押されたら

        if (t!=time(NULL)) {
            t=time(NULL);
            //ミノ降下
            mino_y++;

            if (hit()==1) {
                mino_y--;
                //ミノをフィールドにコピー
                mino_fix_on_field();
                //フィールドをチェックして消す
                field_cheack_and_delet_one_rine();
                //ミノの位置を初期化して形を決める
                mino_decide();
                
            }//ミノを下げてhitした時
        }//時間が獲得されたら

        //fieldコピー
        field_copy_disbuf();
    
        //ミノコピー
        mino_copy_disbuf();

        //dis出力
        disbuf_out();

        //2以上がないか判定することで上に当たっていないか確認、当たっていたら終了
        for (i=0;i<field_h;i++) {
            for (j=0;j<field_w;j++) {
                if (disbuf[i][j]>=2) {
                    return 0;
                }
            }
        }
    }//ループ終了
    return 0;
}