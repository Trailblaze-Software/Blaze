"""Pytest configuration for QGIS plugin tests.

Mocks QGIS modules so pure functions in create_qgis_project.py can be
imported and tested without a running QGIS instance.

Provides the ``create_qgis_project`` fixture-module loaded directly from
the file (bypassing blaze_loader/__init__.py which pulls in dialog code
that cannot run outside QGIS).
"""

import importlib.util
import sys
from pathlib import Path
from unittest.mock import MagicMock

import pytest

# ---------------------------------------------------------------------------
# Mock QGIS modules that are unavailable outside a QGIS runtime.
# Only modules not already present are mocked (so real osgeo is preserved).
# ---------------------------------------------------------------------------
_QGIS_MODULES = [
    "qgis",
    "qgis.core",
    "qgis.PyQt",
    "qgis.PyQt.QtCore",
    "qgis.PyQt.QtWidgets",
    "qgis.PyQt.QtGui",
    "qgis.PyQt.uic",
    "qgis.utils",
]

for _mod_name in _QGIS_MODULES:
    if _mod_name not in sys.modules:
        sys.modules[_mod_name] = MagicMock()

# ---------------------------------------------------------------------------
# Load create_qgis_project.py directly (skip blaze_loader/__init__.py)
# ---------------------------------------------------------------------------
_CREATE_QGIS_PROJECT_PATH = Path(__file__).resolve().parent.parent / "blaze_loader" / "create_qgis_project.py"


@pytest.fixture(scope="session")
def cqp_module():
    """Return the create_qgis_project module loaded directly from file."""
    spec = importlib.util.spec_from_file_location("create_qgis_project", str(_CREATE_QGIS_PROJECT_PATH))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def _load_cqp_module():
    """Eagerly load the module (for use at import-time in test files)."""
    spec = importlib.util.spec_from_file_location("create_qgis_project", str(_CREATE_QGIS_PROJECT_PATH))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod
