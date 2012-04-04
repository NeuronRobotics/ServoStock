all:
	javac *.java

javadoc:
	javadoc -private -d javadoc/ -linksource *.java
