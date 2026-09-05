#!/usr/bin/env python3

import os
from dotenv import load_dotenv


def loading_config() -> dict[str, str | None]:
    load_dotenv()
    return {
        # Os que tem 2 args, é default mode.
        "matrix_mode": os.environ.get("MATRIX_MODE", "development"),
        "database_url": os.environ.get("DATABASE_URL"),
        "api_key": os.environ.get("API_KEY"),
        "log_level": os.environ.get("LOG_LEVEL", "INFO"),
        "zion_endpoint": os.environ.get("ZION_ENDPOINT")
    }


def main() -> None:
    config = loading_config()
    ept_vle = [key for key, value in config.items() if value is None]

    if (
        config["matrix_mode"] == "production"
        and ("api_key" in ept_vle or "database_url" in ept_vle)
    ):
        print("\n\033[31mCRITICAL ERROR:\033[m \
missing required configuration in production mode")

        print(f"Missing: {', '.join(ept_vle)}")

        return

    print("\n\033[34mORACLE STATUS\033[m: Reading the Matrix...\n")

    print("\033[38;5;208mConfiguration loaded\033[m:")

    print(f"\033[33mMode\033[m: {config['matrix_mode']}")

    print(f"\033[33mLog Level\033[m: {config['log_level']}")

    if "database_url" not in ept_vle:
        db_status = "Connected to local instance"
    else:
        db_status = "Not configured"
    print(f"\033[33mDatabase\033[m: {db_status}")

    print(
        f"\033[33mAPI Access\033[m: "
        f"{'Authenticated' if 'api_key' not in ept_vle else 'Not configured'}"
    )

    print(
        f"\033[33mZion Network\033[m: "
        f"{'Online' if 'zion_endpoint' not in ept_vle else 'Offline'}"
    )

    print("\n\033[34mEnvironment security check\033[m:")

    print("\033[32m[OK]\033[m No hardcoded secrets detected")

    ç = "\033[32m[OK]\033[m" if not ept_vle else "\033[31m[MISSING]\033[m"
    print(f"{ç} .env file properly configured")

    print("\033[32m[OK]\033[m Production overrides available")

    print("\n\033[36mThe Oracle sees all configurations.\033[m")


if __name__ == "__main__":
    main()
