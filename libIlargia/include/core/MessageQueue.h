#ifndef ILARGIA_ENGINE_MESSAGE_QUEUE_H
#define ILARGIA_ENGINE_MESSAGE_QUEUE_H

#include <memory>
#include <utility>

namespace Ilargia {

    using MsgUID = unsigned long long;
    const int MSG_TIMEOUT = -1;

    class Message {
        int msgId_;
        MsgUID uniqueId_;
    protected:
        Message(Message &&) = default;

        Message &operator=(Message &&) = default;

    public:
        Message(int msgId);

        virtual ~Message() = default;

        Message(const Message &) = delete;

        Message &operator=(const Message &) = delete;

        virtual std::unique_ptr<Message> move();

        int getMessageId() const;

        MsgUID getUniqueId() const;

    };


    template<typename PayloadType>
    class DataMessage : public Message {
        std::unique_ptr<PayloadType> pl_;
    protected:
        DataMessage(DataMessage &&) = default;

        DataMessage &operator=(DataMessage &&) = default;

    public:
        template<typename ... Args>
        DataMessage(int msgId, Args &&... args)
                : Message(msgId),
                  pl_(new PayloadType(std::forward<Args>(args) ...)) {
        }

        virtual ~DataMessage() = default;

        DataMessage(const DataMessage &) = delete;

        DataMessage &operator=(const DataMessage &) = delete;

        virtual std::unique_ptr<Message> move() override {
            return std::unique_ptr<Message>(new DataMessage<PayloadType>(std::move(*this)));
        }

        PayloadType &getPayload() const {
            return *pl_;
        }

    };


    class Queue {
        class Impl;

        std::unique_ptr<Impl> impl_;

    public:
        Queue();

        ~Queue();

        void put(Message &&msg);

        std::unique_ptr<Message> get(int timeoutMillis = 0);

        std::unique_ptr<Message> request(Message &&msg);

        void respondTo(MsgUID reqUid, Message &&responseMsg);

    };

}

#endif //ILARGIA_ENGINE_QUEUE_H
