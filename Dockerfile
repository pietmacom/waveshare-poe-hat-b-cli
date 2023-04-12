FROM alpine:latest AS builder
RUN apk add gcc make musl-dev libcmis-dev && \
    mkdir -p /build
COPY . /build/
RUN cd /build && \
    make clean && \
    make

FROM alpine:latest
WORKDIR /root
COPY --from=builder /build/waveshare-poe-hat-b-cli /root/
ADD example.sh /root/script.sh
RUN chmod +x /root/script.sh
CMD /root/script.sh


