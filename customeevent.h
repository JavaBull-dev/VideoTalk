#ifndef CUSTOMEEVENT_H
#define CUSTOMEEVENT_H

#include <QEvent>

/**
 * @brief The CustomeEvent class
 * 自定义事件类型
 */
class CustomeEvent : public QEvent
{
public:
    /**
     * @brief The ID enum
     * 类型
     */
    enum ID
    {
        CALL_SUCCESS, OPEN_ERROR, STOP_SUCCESS, CLOSE_APP
    };

    explicit CustomeEvent(ID id);
    static Type type;
    ID getId() const;
private:
    ID id;
};

#endif // CUSTOMEEVENT_H
