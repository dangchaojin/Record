# coding:utf-8
from selenium import webdriver
import time
N = 1
driver=webdriver.Chrome()
driver.get('http://172.16.185.155/meeting/login')
driver.find_element_by_id("email").send_keys("administrator")
driver.find_element_by_id("password").send_keys("888888")
driver.find_element_by_id("login-submit").click()
time.sleep(5)
driver.find_element_by_xpath("/html/body/div[3]/div/div[2]/div/a[4]/div[2]").click()
while N <= 1000:
    time.sleep(3)
    #进入个人模板
    driver.find_element_by_xpath('//*[@id="myTemplate"]/a').click()
    time.sleep(3)
    # 选择一个会议模板并立即召开
    driver.find_element_by_xpath('//*[@id="tbody_datagrid-row-r1-2-0"]/td[2]/div/input').click()
    time.sleep(3)
    # 选中模板立即召开
    driver.find_element_by_xpath('//*[@id="tpl-handle-div"]/div[2]/div[1]/a').click()
    time.sleep(3)
    # 弹框处理勾选永久会议
    #driver.find_element_by_xpath('//*[@id="checkbox1_eins"]').click()
    # 点击确认
    driver.find_element_by_xpath('//*[@id="meetingLastTimeDialog_layer-btn-ok"]/a').click()
    time.sleep(5)
    #返回个人模板
    driver.back()

    time.sleep(3)
    # 选模板2------------------------------------------------------
    driver.find_element_by_xpath('//*[@id="tbody_datagrid-row-r1-2-1"]/td[2]/div/input').click()
    time.sleep(3)
    # 选中模板立即召开
    driver.find_element_by_xpath('//*[@id="tpl-handle-div"]/div[2]/div[1]/a').click()
    time.sleep(3)
    # 点击确认
    driver.find_element_by_xpath('//*[@id="meetingLastTimeDialog_layer-btn-ok"]/a').click()
    time.sleep(5)
    #返回个人模板
    driver.back()

    time.sleep(3)
    # 选模板2------------------------------------------------------
    driver.find_element_by_xpath('//*[@id="tbody_datagrid-row-r1-2-2"]/td[2]/div/input').click()
    time.sleep(3)
    # 选中模板立即召开
    driver.find_element_by_xpath('//*[@id="tpl-handle-div"]/div[2]/div[1]/a').click()
    time.sleep(3)
    # 点击确认
    driver.find_element_by_xpath('//*[@id="meetingLastTimeDialog_layer-btn-ok"]/a').click()
    time.sleep(5)
    #返回个人模板
    driver.back()

    time.sleep(5)
    #进入会议管理页面
    driver.find_element_by_xpath('//*[@id="webmcc"]/a').click()
    time.sleep(5)
    #点击结束会议
    driver.find_element_by_xpath('//*[@id="meetingListContainer"]/div/div[3]/div[1]/a').click()
    time.sleep(5)
    #点击确定按钮
    driver.find_element_by_xpath('/html/body/div[1]/div/table/tbody/tr[2]/td[2]/div/table/tbody/tr[2]/td[2]/div/div/div[4]/span[1]/a').click()
    time.sleep(5)
    #点击结束会议
    driver.find_element_by_xpath('//*[@id="meetingListContainer"]/div/div[3]/div[1]/a').click()
    time.sleep(5)
    #点击确定按钮
    driver.find_element_by_xpath('/html/body/div[1]/div/table/tbody/tr[2]/td[2]/div/table/tbody/tr[2]/td[2]/div/div/div[4]/span[1]/a').click()
    time.sleep(5)
    #点击结束会议
    driver.find_element_by_xpath('//*[@id="meetingListContainer"]/div/div[3]/div[1]/a').click()
    time.sleep(5)
    #点击确定按钮
    driver.find_element_by_xpath('/html/body/div[1]/div/table/tbody/tr[2]/td[2]/div/table/tbody/tr[2]/td[2]/div/div/div[4]/span[1]/a').click()
    time.sleep(3)

    print('拷机次数:', N, time.ctime())
    N += 1
    #driver.close()


