<%@ page import="java.io.*,java.util.*, java.net.*" %>

Time: <%= (new java.util.Date()).toLocaleString()%>
<%
   InetAddress ia = InetAddress.getLocalHost();
   String node = ia.getHostName();
   out.println("hostname:  " + node + " ...sleep 3.....");
%>
<%
   for(int n=1;n<191;n++){
      Thread.sleep(10000);
   }
%>

Time: <%= (new java.util.Date()).toLocaleString()%>
<%
   InetAddress ia2 = InetAddress.getLocalHost();
   String node2 = ia2.getHostName();
%>
