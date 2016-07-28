FROM centos:centos7

RUN yum install -y http://dl.fedoraproject.org/pub/epel/7/x86_64/e/epel-release-7-2.noarch.rpm
RUN yum install -y python-pip python-devel nginx gcc mysql-devel

RUN echo "daemon off;" >> /etc/nginx/nginx.conf
ADD exampleapp.conf /etc/nginx/conf.d/exampleapp.conf

RUN pip install django gunicorn MySQL-python

ADD ./ /var/www/exampleapp
WORKDIR /var/www/exampleapp
RUN chmod +x entrypoint.sh

EXPOSE 80

ENTRYPOINT ./entrypoint.sh
