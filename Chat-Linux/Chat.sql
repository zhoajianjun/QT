-- MySQL dump 10.13  Distrib 5.5.41, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: Chat
-- ------------------------------------------------------
-- Server version	5.5.41-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `ChatGroup`
--

DROP TABLE IF EXISTS `ChatGroup`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ChatGroup` (
  `ChatGroupID` varchar(10) NOT NULL,
  `UserID` varchar(10) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ChatGroup`
--

LOCK TABLES `ChatGroup` WRITE;
/*!40000 ALTER TABLE `ChatGroup` DISABLE KEYS */;
INSERT INTO `ChatGroup` VALUES ('123','123'),('123','234'),('123','345'),('234','123'),('234','234'),('234','345'),('234','456'),('234','567');
/*!40000 ALTER TABLE `ChatGroup` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ChatGroupInfo`
--

DROP TABLE IF EXISTS `ChatGroupInfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ChatGroupInfo` (
  `ChatGroupID` varchar(10) NOT NULL,
  `ChatGroupName` varchar(30) CHARACTER SET gbk DEFAULT NULL,
  `ChatGroupAdminID` varchar(10) DEFAULT NULL,
  `ChatGroupNum` int(11) DEFAULT NULL,
  `ChatGroupInfocol` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`ChatGroupID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ChatGroupInfo`
--

LOCK TABLES `ChatGroupInfo` WRITE;
/*!40000 ALTER TABLE `ChatGroupInfo` DISABLE KEYS */;
INSERT INTO `ChatGroupInfo` VALUES ('123','我的室友','123',3,'123Group.png'),('234','好友群','234',5,'23Group.png');
/*!40000 ALTER TABLE `ChatGroupInfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `GroupTable`
--

DROP TABLE IF EXISTS `GroupTable`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `GroupTable` (
  `UserID` varchar(10) NOT NULL,
  `GroupName` varchar(30) CHARACTER SET gbk NOT NULL,
  `FriendID` varchar(10) NOT NULL,
  PRIMARY KEY (`UserID`,`FriendID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `GroupTable`
--

LOCK TABLES `GroupTable` WRITE;
/*!40000 ALTER TABLE `GroupTable` DISABLE KEYS */;
INSERT INTO `GroupTable` VALUES ('123','我的宿舍','234'),('123','我的宿舍','345'),('123','我的班级','456'),('123','好兄弟','678'),('123','好兄弟','789'),('234','哈哈哈','123'),('234','哈哈哈','345');
/*!40000 ALTER TABLE `GroupTable` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `User`
--

DROP TABLE IF EXISTS `User`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `User` (
  `UserID` varchar(10) NOT NULL,
  `Password` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`UserID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `User`
--

LOCK TABLES `User` WRITE;
/*!40000 ALTER TABLE `User` DISABLE KEYS */;
INSERT INTO `User` VALUES ('123','202cb962ac59075b964b07152d234b70'),('234','289dff07669d7a23de0ef88d2f7129e7'),('345','d81f9c1be2e08964bf9f24b15f0e4900'),('456','250cf8b51c773f3f8dc8b4be867a9a02'),('567','99c5e07b4d5de9d18c350cdf64c5aa3d'),('678','9fe8593a8a330607d76796b35c64c600'),('789','68053af2923e00204c3ca7c6a3150cf7');
/*!40000 ALTER TABLE `User` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `UserInfo`
--

DROP TABLE IF EXISTS `UserInfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `UserInfo` (
  `UserID` varchar(10) NOT NULL,
  `UserName` varchar(20) CHARACTER SET gbk DEFAULT NULL,
  `UserSex` varchar(10) CHARACTER SET gbk DEFAULT NULL,
  `UserAge` int(11) DEFAULT NULL,
  `UserAddress` varchar(45) CHARACTER SET gbk DEFAULT NULL,
  `UserPS` varchar(45) CHARACTER SET gbk DEFAULT NULL,
  `UserAvatar` varchar(45) CHARACTER SET gbk DEFAULT NULL,
  PRIMARY KEY (`UserID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `UserInfo`
--

LOCK TABLES `UserInfo` WRITE;
/*!40000 ALTER TABLE `UserInfo` DISABLE KEYS */;
INSERT INTO `UserInfo` VALUES ('123','李四','男',21,'芜湖','程序猿！！！','123.png'),('234','张三','男',22,'马鞍山','我的未来我做主！！！','234.png'),('345','王麻子','男',23,'合肥','青春在哪','345.png'),('456','王小花','女',22,'淮北','青春张狂，思绪飞扬！！！','456.png'),('567','赵铁柱','男',21,'马鞍山','呵呵呵','567.png'),('678','王二丫','女',20,'合肥','静静的。。。','678.png'),('789','刘铁蛋','男',22,'淮北','流年似水。。。','789.png');
/*!40000 ALTER TABLE `UserInfo` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-07-02 21:50:30
