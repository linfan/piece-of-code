FROM alpine:edge

# Add python3
RUN apk add --no-cache python3 \
    && python3 -m ensurepip \
    && rm -r /usr/lib/python*/ensurepip \
    && pip3 install --upgrade pip setuptools \
    && if [ ! -e /usr/bin/pip ]; then ln -s pip3 /usr/bin/pip ; fi \
    && if [[ ! -e /usr/bin/python ]]; then ln -sf /usr/bin/python3 /usr/bin/python; fi \
    && rm -r /root/.cache

# Add Chrome
RUN apk -U --no-cache --allow-untrusted add chromium-chromedriver chromium \
    && rm -rf /var/lib/apt/lists/* var/cache/apk/* /usr/share/man /tmp/*

# Add Firefox
RUN wget https://github.com/mozilla/geckodriver/releases/download/v0.23.0/geckodriver-v0.23.0-linux64.tar.gz \
	&& tar -C /usr/bin -zxf geckodriver-v0.23.0-linux64.tar.gz  \
	&& rm geckodriver-v0.23.0-linux64.tar.gz \
	&& apk add -U --no-cache --repository http://dl-3.alpinelinux.org/alpine/edge/testing/ --allow-untrusted firefox \
    && rm -rf /var/lib/apt/lists/* var/cache/apk/* /usr/share/man /tmp/*

# Add script
COPY requirements.txt /tmp/
COPY screenshot.py /opt/bin/
RUN pip install -r /tmp/requirements.txt \
    && chmod +x /opt/bin/screenshot.py \
    && rm -f /tmp/requirements.txt
ENTRYPOINT ["/opt/bin/screenshot.py"]