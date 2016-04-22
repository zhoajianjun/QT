Name:           MeetingPanel
Version:        1.8.4
Release:        1%{?dist}
Summary:        AMP1690 MeetingPanel

License:        bqvision
Vendor:         bqvision
URL:            http://www.bqvision.com
Source0:        %{name}.tar.gz
Source1:        %{name}.sh
Source2:        %{name}.desktop
Source3:        %{name}.png
Source4:        qt.conf

AutoReqProv:    no
Requires:       qt5 >= 5.5

%description
AMP1690 MeetingPanel


%define _bqvisiondir  /usr/bqvision
%define _mpdir %{_bqvisiondir}/MeetingPanel

%prep
%setup -n MeetingPanel


%install
rm -rf $RPM_BUILD_ROOT
mkdir -p %{buildroot}%{_mpdir}
install bin/%{name} %{buildroot}%{_mpdir}
install %{SOURCE1} %{SOURCE3} %{SOURCE4} %{buildroot}%{_mpdir}
mkdir -p %{buildroot}%{_datadir}/applications
install %{SOURCE2} %{buildroot}%{_datadir}/applications/


%files
%defattr(-,root,root,-)
%dir %{_mpdir}
%{_mpdir}/*
%dir %{_datadir}/applications
%{_datadir}/applications/%{name}.desktop

%post
if [ "x$1" = "x1" ]; then
    if [ -d ~/Desktop ]; then
        ln -sf %{_datadir}/applications/%{name}.desktop ~/Desktop
    fi
    if [ -d ~/桌面 ]; then
        ln -sf %{_datadir}/applications/%{name}.desktop ~/桌面
    fi
fi

%preun
if [ "x$1" = "x0" ]; then
    unlink ~/Desktop/%{name}.desktop > /dev/null 2>&1
    unlink ~/桌面/%{name}.desktop > /dev/null 2>&1
    exit 0
fi

%changelog
