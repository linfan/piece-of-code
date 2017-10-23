# 演示通过MQ实现最终一致性
---

场景：A服务转账给B服务，且两个服务各自使用独立的数据库。

## 本地运行环境构建

### 消息队列服务

#### 创建消息队列服务并配置用户密码

```
docker run -d --hostname rabbit --name rabbit \
    -e RABBITMQ_DEFAULT_USER=demo \
    -e RABBITMQ_DEFAULT_PASS=password \
    -p 5672:5672 -p 15672:15672 \
    rabbitmq:3-management
```

RabbitMQ使用`5672`端口，管理界面使用`15672`端口。

### 数据库

#### 创建数据库并配置用户密码

```
docker run -d --name mysql \
    -e MYSQL_ROOT_PASSWORD=password \
    -e MYSQL_USER=demo \
    -e MYSQL_PASSWORD=password \
    -p 3306:3306 \
    mysql:5
```

MySQL使用`3306`端口。

#### 初始化数据库用户权限和表结构

配置数据库权限

```
GRANT ALL PRIVILEGES ON demo_db1 . * TO 'demo'@'%';
GRANT ALL PRIVILEGES ON demo_db2 . * TO 'demo'@'%';
FLUSH PRIVILEGES;
```

初始化数据表

```
CREATE DATABASE demo_db1;
USE demo_db1;
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
  `id` BIGINT(20) NOT NULL AUTO_INCREMENT COMMENT '主键id',
  `userName` VARCHAR(32) COMMENT '用户名',
  `accountBalance` DECIMAL(30,2) DEFAULT 0 COMMENT '账户余额',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `transaction`;
CREATE TABLE `transaction` (
  `id` BIGINT(20) NOT NULL AUTO_INCREMENT COMMENT '主键id',
  `userId` BIGINT(20) COMMENT '用户ID',
  `amount` DECIMAL(30,2) DEFAULT 0 COMMENT '转账金额',
  `timestamp` TIMESTAMP COMMENT '交易时间',
  `transactionId` VARCHAR(50) COMMENT '交易ID',
  `status` VARCHAR(15) COMMENT '交易状态',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8;

CREATE DATABASE demo_db2;
USE demo_db2;
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '主键id',
  `userName` VARCHAR(32) COMMENT '用户名',
  `accountBalance` DECIMAL(30,2) DEFAULT 0 COMMENT '账户余额',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `transaction`;
CREATE TABLE `transaction` (
  `id` BIGINT(20) NOT NULL AUTO_INCREMENT COMMENT '主键id',
  `userId` BIGINT(20) COMMENT '用户ID',
  `amount` DECIMAL(30,2) DEFAULT 0 COMMENT '转账金额',
  `timestamp` TIMESTAMP COMMENT '交易时间',
  `transactionId` VARCHAR(50) COMMENT '交易ID',
  `status` VARCHAR(15) COMMENT '交易状态',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8;
```

## 服务构建和启动

```
cd transaction
mvn clean package
java -jar receiver/target/receiver-1.0.0-SNAPSHOT.jar
java -jar sender/target/sender-1.0.0-SNAPSHOT.jar
```
