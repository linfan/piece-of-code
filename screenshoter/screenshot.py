#!/usr/bin/env python3

from optparse import OptionParser
from selenium import webdriver
from selenium.webdriver.chrome.options import Options

# Size Format: width[,height]
WINDOW_SIZE = "1250,1250"
#WINDOW_SIZE = "1920,1080"

def get_firefox_driver():
    firefox_path = '/usr/bin/firefox'
    firefox_options = Options()
    firefox_options.add_argument("--headless")
    firefox_options.add_argument("--window-size=%s" % WINDOW_SIZE)
    firefox_options.binary = firefox_path
    firefox_options.profile = webdriver.FirefoxProfile()
    return webdriver.Firefox(
        firefox_options=firefox_options,
        log_path="/tmp/geckodriver.log"
    )

def get_chrome_driver():
    chrome_path = '/usr/bin/chromium-browser'
    chromedriver_path = '/usr/bin/chromedriver'
    chrome_options = Options()
    chrome_options.add_argument("--headless")
    chrome_options.add_argument("--no-sandbox")
    chrome_options.add_argument("--window-size=%s" % WINDOW_SIZE)
    chrome_options.binary_location = chrome_path
    return webdriver.Chrome(
        executable_path=chromedriver_path,
        chrome_options=chrome_options,
        service_args=['--verbose'],
        service_log_path="/tmp/chromedriver.log"
    )

def make_screenshot(driver, url, output):
    if not url.startswith('file://'):
        raise Exception('URLs need to start with "file://"')
    driver.get(url)
    width = driver.execute_script("return Math.max(document.body.scrollWidth, document.body.offsetWidth, "
                                  "document.documentElement.clientWidth, document.documentElement.scrollWidth, "
                                  "document.documentElement.offsetWidth);")
    height = driver.execute_script("return Math.max(document.body.scrollHeight, document.body.offsetHeight, "
                                   "document.documentElement.clientHeight, document.documentElement.scrollHeight, "
                                   "document.documentElement.offsetHeight);")
    driver.set_window_size(width, height)
    driver.save_screenshot(output)
    driver.close()

if __name__ == '__main__':
    usage = "usage: %prog [options] <url> <output>"
    parser = OptionParser(usage=usage)
    (options, args) = parser.parse_args()
    if len(args) < 2:
        parser.error("please specify an URL and a output path")

    driver = get_chrome_driver()
    #driver = get_firefox_driver()
    make_screenshot(driver, args[0], args[1])
