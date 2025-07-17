git clone https://github.com/OpenAlbion/api.git openalbion
cd openalbion
composer install
cp .env.example .env
php artisan key:generate
php artisan migrate
