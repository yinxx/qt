#ifndef GLDTIPBOX_H
#define GLDTIPBOX_H

#include "GLDFileUtils.h"

#include <QWidget>

class QLabel;
class QPushButton;
class QPropertyAnimation;
class QGraphicsOpacityEffect;

static QWidget* topParentWidget(QWidget* pWgt)
{
    if (!pWgt)
    {
        return nullptr;
    }

    QWidget* widget = nullptr;

    for (widget = pWgt; widget != nullptr; widget = widget->parentWidget())
    {
        if (widget->isWindow())
        {
            break;
        }
    }

    return widget;
}

// 数据参数类
// 注意：如果文字中要加入链接，请遵循html的定义，例如：<a href=\"http://www.baidu.com/\">title</a>
class GLDMaskBoxParam
{
public:
    GLDMaskBoxParam() :
        //m_sizeMinTipBox(300, 160),
        //m_sizeMaxTipBox(435, 0),
        m_nMaxWidth(435),
        m_nRowHeight(20),
        m_sizeArrow(20, 12),
        m_nTimeFadeOut(2000),
        m_nTimeRemain(8000),
        m_fontBody(QFont(TRANS_STRING("微软雅黑"), 9, QFont::Normal)),
        m_clrBody(QColor("#434343")),
        m_fontTitle(QFont(TRANS_STRING("微软雅黑"), 12, QFont::Bold)),
        m_clrTitle(Qt::blue),
        m_sizeIcon(16, 16),
        m_wgtOwner(NULL),
        m_strIcon(exePath() + "/images/Msg/warring.png"),
        m_strIconClose(exePath() + "/images/Msg/close.png"),
        m_strTitle(TRANS_STRING("提示")),
        m_strBody(TRANS_STRING("提示")),
        m_bIsOverTimeShow(false)
    {

    }

    GLDMaskBoxParam& operator=(GLDMaskBoxParam& param)
    {
        m_strIcon = param.m_strIcon;
        m_strIconClose = param.m_strIconClose;
        m_strTitle = param.m_strTitle;
        m_fontTitle = param.m_fontTitle;
        m_clrTitle = param.m_clrTitle;
        m_nRowHeight = param.m_nRowHeight;
        m_strBody = param.m_strBody;
        m_fontBody = param.m_fontBody;
        m_clrBody = param.m_clrBody;
        m_nTimeRemain = param.m_nTimeRemain;
        m_nTimeFadeOut = param.m_nTimeFadeOut;
        m_sizeArrow = param.m_sizeArrow;
        //m_sizeMinTipBox = param.m_sizeMinTipBox;
        //m_sizeMaxTipBox = param.m_sizeMaxTipBox;
        m_sizeIcon = param.m_sizeIcon;
        //m_bIsWin = param.m_bIsWin;
        m_wgtOwner = param.m_wgtOwner;
        m_bIsOverTimeShow = param.m_bIsOverTimeShow;

        return *this;
    }

    QString m_strIcon;      // 图标全路径
    QString m_strIconClose; // 关闭图标路径
    QSize   m_sizeIcon;     // 图标的大小

    QString m_strTitle;     // titile文字
    QFont m_fontTitle;      // title文字字体
    QColor m_clrTitle;      // titile文字颜色

    QString m_strBody;      // 正文文字
    QFont m_fontBody;       // 正文文字字体
    QColor m_clrBody;       // 正文文字颜色
    int m_nRowHeight;       // 正文行高

    int m_nTimeRemain;      // 停留时间（milliseconds）
    int m_nTimeFadeOut;     // 淡出时间(milliseconds)

    QSize m_sizeArrow;      // 箭头大小（作为内容layout的外边距）
    //QSize m_sizeMinTipBox;  // tipbox控件的大小
    //QSize m_sizeMaxTipBox;  // tipbox的最大大小（换行依据）
    int m_nMaxWidth;        // 最大宽度，换行依据

    //bool m_bIsWin;          // [保留]是否是独立窗口（不受外围窗体的约束，如果是false，则自动将owner的父设置为自身的父）
    QWidget * m_wgtOwner;   // 被指向的widget

    bool m_bIsOverTimeShow; // 是否超时显示，默认false
};

class GLDMaskBox : public QWidget
{
    Q_OBJECT

public:
    static GLDMaskBox * showTipBox(QWidget * wgtOwner, const QString & strTitle, const QString & strBody);

    static GLDMaskBox * showTipBox(GLDMaskBoxParam * pParam);

    static void closeThis();

    QString objectName() const
    {
        return QString("QTipBox");
    }

public:
    GLDMaskBoxParam& tipBoxParam();

    /**
     * @brief 立即关闭,并销毁
     */
    virtual void immediateCloseThis();

    virtual QSize sizeHint() const;

protected:
    virtual void showEvent(QShowEvent * event);

    virtual void paintEvent(QPaintEvent * event);

    virtual void mousePressEvent(QMouseEvent *e);

    virtual bool eventFilter(QObject *obj, QEvent *ev);

    /**
     * @brief 建立圆角矩形的tip path
     * @return
     */
    virtual QPainterPath buildPathRoundRectTip();

    virtual QPoint calcPosOfOwner();


    GLDMaskBoxParam          m_oTipBoxParam;

    QLabel*                 m_labelIco;                       // 图标
    QLabel*                 m_labelTextTitle;                 // 标题文字区
    QLabel*                 m_labelTextBody;                  // 内容文字区
    QTimer*                 m_timerClose;                     // 关闭定时器
    QPushButton*            m_btnClose;                       // 关闭按钮
    QPropertyAnimation*     m_animFadeOut;                    // 渐隐效果动画
    QGraphicsOpacityEffect* m_effectOpacity;                  // 渐隐效果

private:
    explicit GLDMaskBox(GLDMaskBoxParam & oTipBoxParam, QWidget *parent = 0);

    static QPointer<GLDMaskBox> m_pTipBox;

public slots:
    void slotClose();

protected slots:
    void slotCloseTimer();
    void slotFadeout();
};

#endif // GLDTIPBOX_H
