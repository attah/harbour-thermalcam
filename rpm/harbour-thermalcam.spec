Name:       harbour-thermalcam

Summary:    ThermalCam
Version:    0
Release:    1
License:    GPLv3
URL:        https://github.com/attah/harbour-thermalcam
Source0:    %{name}-%{version}.tar.bz2
Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(sailfishapp) >= 1.0.2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  desktop-file-utils
BuildRequires:  opencv-devel

%description
Simple thermal camera viewer app for Topdon TC001, InfiRay P2 Pro and similar devices.

%if "%{?vendor}" == "chum"
PackageName: ThermalCam
Type: desktop-application
DeveloperName: attah
Categories:
 - Media
Custom:
  Repo: https://github.com/attah/harbour-thermalcam
Icon: https://raw.githubusercontent.com/attah/harbour-thermalcam/master/icons/172x172/harbour-thermalcam.png
Url:
  Homepage: https://github.com/attah/harbour-thermalcam
%endif

%prep
%setup -q -n %{name}-%{version}

%build

%qmake5

%make_build


%install
%qmake5_install


desktop-file-install --delete-original         --dir %{buildroot}%{_datadir}/applications                %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
